import argparse
import subprocess
import shutil
import os
import difflib
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


def merge_stubs(old_stub: Path, new_stub: Path):
    """Append differences from new_stub to old_stub (naive line-based)."""
    with old_stub.open("r", encoding="utf-8") as f:
        old_lines = f.readlines()
    with new_stub.open("r", encoding="utf-8") as f:
        new_lines = f.readlines()

    diff = list(difflib.unified_diff(old_lines, new_lines, lineterm=""))
    additions = [line[1:] for line in diff if line.startswith("+") and not line.startswith("+++")]

    if additions:
        with old_stub.open("a", encoding="utf-8") as f:
            f.write("\n# --- AUTO-GENERATED APPEND ---\n")
            f.writelines(additions)
        print(f"Appended {len(additions)} new lines to {old_stub}")
    else:
        print(f"No changes detected for {old_stub}")


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
        description="Incrementally generate and merge stubs for monolith modules"
    )
    parser.add_argument(
        "modules",
        nargs="+",
        help="Modules to stub (e.g. monolith.planets monolith.dynamics)",
    )
    args = parser.parse_args()
    main(args.modules)
