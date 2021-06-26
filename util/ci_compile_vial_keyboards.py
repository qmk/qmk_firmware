#!/usr/bin/env python3
from glob import glob
import subprocess
import sys


def main():
    for filename in glob("keyboards/**/vial.json", recursive=True):
        filename = filename[10:-10]
        cmd = filename.split("/keymaps/")[0]
        # compile default
        ret_default = subprocess.call(["make", cmd + ":default", "-j4"])
        # compile via
        ret_via = subprocess.call(["make", cmd + ":via", "-j4"])

        if ret_default != 0 or ret_via != 0:
            sys.exit(1)


if __name__ == "__main__":
    main()
