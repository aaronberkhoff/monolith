import argparse
import subprocess
import shutil
import ast
from pathlib import Path

PY_FOLDER = Path("python/monolith")
STUB_TMP = PY_FOLDER / "stubs_tmp"


def run_stubgen(module: str) -> Path:
    """Run pybind11-stubgen and return the path to the generated .pyi."""
    subprocess.run(
        ["pybind11-stubgen", module, "--output-dir", str(STUB_TMP)],
        check=True,
    )
    mod_parts = module.split(".")
    return STUB_TMP.joinpath(*mod_parts).with_suffix(".pyi")


def get_definitions(tree: ast.AST):
    """Extract top-level function and class names."""
    defs = {}
    for node in tree.body:
        if isinstance(node, ast.FunctionDef):
            defs[node.name] = node
        elif isinstance(node, ast.ClassDef):
            defs[node.name] = node
    return defs


def get_class_members(node: ast.ClassDef):
    """Extract method/attribute names from a class AST."""
    members = {}
    for item in node.body:
        if isinstance(item, ast.FunctionDef):
            members[item.name] = item
        elif isinstance(item, ast.AnnAssign) and isinstance(item.target, ast.Name):
            members[item.target.id] = item
    return members


def merge_stubs(old_path: Path, new_path: Path):
    """Merge new stub definitions into old stub (AST-aware)."""
    with old_path.open("r", encoding="utf-8") as f:
        old_src = f.read()
    with new_path.open("r", encoding="utf-8") as f:
        new_src = f.read()

    old_tree = ast.parse(old_src)
    new_tree = ast.parse(new_src)

    old_defs = get_definitions(old_tree)
    new_defs = get_definitions(new_tree)

    changes = []

    for name, new_def in new_defs.items():
        if name not in old_defs:
            # New top-level def/class → append
            old_tree.body.append(new_def)
            changes.append(f"Added {name}")
        else:
            # If it's a class, merge members
            if isinstance(new_def, ast.ClassDef) and isinstance(old_defs[name], ast.ClassDef):
                old_members = get_class_members(old_defs[name])
                new_members = get_class_members(new_def)
                for mname, mdef in new_members.items():
                    if mname not in old_members:
                        old_defs[name].body.append(mdef)
                        changes.append(f"Added {name}.{mname}")

    if changes:
        print(f"Merged changes into {old_path}: {changes}")
        new_code = ast.unparse(old_tree)  # requires Python 3.9+
        with old_path.open("w", encoding="utf-8") as f:
            f.write(new_code)
    else:
        print(f"No new definitions to merge for {old_path}")


def generate_and_merge(module: str):
    print(f"Processing {module}...")
    new_stub = run_stubgen(module)
    dest = PY_FOLDER.joinpath(*module.split(".")[1:]).with_suffix(".pyi")
    dest.parent.mkdir(parents=True, exist_ok=True)

    if dest.exists():
        merge_stubs(dest, new_stub)
    else:
        shutil.copy2(new_stub, dest)
        print(f"Created new stub: {dest}")

    shutil.rmtree(STUB_TMP)


def main(modules: list[str]):
    for module in modules:
        generate_and_merge(module)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Incrementally generate and merge stubs (AST-aware)"
    )
    parser.add_argument(
        "modules",
        nargs="+",
        help="Modules to stub (e.g. monolith.planets monolith.dynamics)",
    )
    args = parser.parse_args()
    main(args.modules)
