#!/usr/bin/env python3
from glob import glob
import subprocess


def main():
    for filename in glob("keyboards/**/vial.json", recursive=True):
        filename = filename[10:-10]
        cmd = filename.split("/keymaps/")[0]
        # compile default
        subprocess.call(["make", cmd + ":default", "-j4"])
        # compile via
        subprocess.call(["make", cmd + ":via", "-j4"])


if __name__ == "__main__":
    main()
