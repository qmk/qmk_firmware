import sys
import re
import struct
import hashlib
import time


def main():
    inp = sys.argv[1]
    out = sys.argv[2]
    configs = sys.argv[3:]

    # identify keyboard UID
    uid = None
    for config in configs:
        with open(config, "r") as inf:
            for line in inf:
                uid = re.findall(r"#define.*VIAL_KEYBOARD_UID.*{(.*)}", line)
                if uid:
                    break
        if uid:
            break
    if not uid:
        print("Cannot identify keyboard UID from configuration files {}, ensure that you have VIAL_KEYBOARD_UID defined!".format(configs))
        return 1

    uid = uid[0].split(",")
    uid = [int(x, 16) for x in uid]
    uid = struct.pack("BBBBBBBB", *uid)

    # read firmware binary
    with open(sys.argv[1], "rb") as inf:
        firmware = inf.read()

    with open(out, "wb") as outf:
        outf.write(b"VIALFW01")
        outf.write(uid)
        outf.write(struct.pack("<Q", int(time.time())))
        outf.write(b"\x00" * 8)
        outf.write(hashlib.sha256(firmware).digest())
        outf.write(firmware)

    print("-" * 80)
    print("Vial update package created at {}".format(out))
    print("-" * 80)

    return 0


if __name__ == "__main__":
    sys.exit(main())
