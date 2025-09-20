import argparse
import subprocess
import shutil
import os

PY_FOLDER = "python/monolith"
STUB_TMP = os.path.join(PY_FOLDER, "stubs")

def main(module: str):
    print(f"Generating stubs for {module}...")
    subprocess.run(
        ["pybind11-stubgen", module, "--output-dir", STUB_TMP],
        check=True
    )

    # Figure out the module name and copy stubs into package root
    mod_parts = module.split(".")
    dest = os.path.join(PY_FOLDER, *mod_parts[1:]) + ".pyi"

    src = os.path.join(STUB_TMP, *mod_parts) + ".pyi"
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    shutil.copy(src, dest)

    shutil.rmtree(STUB_TMP)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate stubs for monolith modules")
    parser.add_argument("modules", nargs="+", help="Modules to stub (e.g. monolith.planets monolith.dynamics)")
    args = parser.parse_args()

    for module in args.modules:
        main(module)
