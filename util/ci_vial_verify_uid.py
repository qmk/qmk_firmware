#!/usr/bin/env python3
from glob import glob
import os
import re
import sys
import struct
from collections import defaultdict


def main():
    error = 0
    uid_to_keyboards = defaultdict(set)

    for filename in glob("keyboards/**/vial.json", recursive=True):
        keyboard = filename[10:-10].split("/keymaps/")[0]

        path = os.path.dirname(filename)
        uid = None
        while True:
            config_h = os.path.join(path, "config.h")
            if os.path.exists(config_h):
                with open(config_h, "r") as inf:
                    for line in inf:
                        uid = re.findall(r"#define.*VIAL_KEYBOARD_UID.*{(.*)}", line)
                        if uid:
                            break
            if uid:
                break
            path = os.path.dirname(path)
            if path.endswith("keyboards"):
                break

        if not uid:
            print("Keyboard {} does not define a VIAL_KEYBOARD_UID".format(keyboard))
            error = 1
            continue

        uid = uid[0].split(",")
        uid = [int(x, 16) for x in uid]
        uid = struct.pack("BBBBBBBB", *uid).hex()
        uid_to_keyboards[uid].add(keyboard)

        print("{} uses UID {}".format(keyboard, uid))

    for uid, keyboards in uid_to_keyboards.items():
        if len(keyboards) > 1:
            print("UID {} duplicated: {}".format(uid, keyboards))
            error = 1

    return error

if __name__ == "__main__":
    sys.exit(main())
