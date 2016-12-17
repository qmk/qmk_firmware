"""
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
"""

import sys
sys.path.append("ProjectGenerator")


def show_message(message):
    print("[Project Generator] %s" % message)
    sys.stdout.flush()


def main(lufa_root_path):
    try:
        from asf_avrstudio5_interface import PythonFacade
    except ImportError:
        print("Fatal Error: The ASF project generator is missing.")
        return 1

    p = PythonFacade(lufa_root_path)

    show_message("Checking database sanity...")
    p.check_extension_database_sanity(lufa_root_path)

    show_message("Building cache files...")
    p.generate_extension_cache_files(lufa_root_path)

    show_message("Cache files created.")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1]))
