import os
import sys
import platform
import tarfile
import zipfile
import urllib.request
import subprocess
from pathlib import Path

BASE_URL = "https://naif.jpl.nasa.gov/pub/naif/toolkit//"
DEST_DIR = Path("third_party/")
DATA_DIR = Path("data/kernels")  # directory to save SPICE kernels

def download_file(url: str, dest: Path):
    dest.parent.mkdir(parents=True, exist_ok=True)
    print(f"Downloading {url} -> {dest}")
    urllib.request.urlretrieve(url, dest)
    return dest

def extract_tar_z(path: Path, dest: Path):
    tar_path = path.with_suffix("")  # remove .Z
    subprocess.run(["uncompress", "-f", str(path)], check=True)
    with tarfile.open(tar_path, "r:") as tar:
        tar.extractall(dest)

def extract_zip(path: Path, dest: Path):
    with zipfile.ZipFile(path, "r") as zf:
        zf.extractall(dest)

def download_cspice():
    system = platform.system().lower()

    if system == "linux":
        filename = "cspice.tar.Z"
        url = BASE_URL + "C/PC_Linux_GCC_64bit/packages/" + filename
    elif system == "darwin":  # macOS
        filename = "cspice.tar.Z"
        url = BASE_URL + "C/MacIntel_OSX_clang_64bit/packages/" + filename
    elif system == "windows":
        filename = "cspice.zip"
        url = BASE_URL + "C/PC_Windows_VisualC_64bit/packages/" + filename
    else:
        raise RuntimeError(f"Unsupported system: {system}")

    archive_path = DEST_DIR / filename
    download_file(url, archive_path)

    print(f"Extracting {archive_path}...")
    if filename.endswith(".tar.Z"):
        extract_tar_z(archive_path, DEST_DIR)
    elif filename.endswith(".zip"):
        extract_zip(archive_path, DEST_DIR)

    print(f"CSPICE ready in {DEST_DIR}")

def download_kernels():
    """
    Downloads a set of example SPICE kernels into the data directory.
    You can modify this list based on the kernels you need.
    """
    DATA_DIR.mkdir(parents=True, exist_ok=True)

    kernels = [
        # Example: planetary ephemeris
        ("spk/planets", "de442s.bsp"),
        # Leap seconds
        ("lsk", "naif0012.tls"),
        # Planetary constants
        ("pck", "pck00010.tpc")
    ]

    base_kernel_url = "https://naif.jpl.nasa.gov/pub/naif/generic_kernels/"

    for ktype, kfile in kernels:
        url = f"{base_kernel_url}{ktype}/{kfile}"
        dest = DATA_DIR / kfile
        if not dest.exists():
            print(f"Downloading {ktype} kernel: {kfile}")
            download_file(url, dest)
        else:
            print(f"Kernel already exists: {kfile}")

    print(f"All SPICE kernels are ready in {DATA_DIR}")

def main():
    download_cspice()
    download_kernels()

if __name__ == "__main__":
    main()
