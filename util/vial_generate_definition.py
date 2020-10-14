#!/usr/bin/env python3
import sys
import json
import lzma

def main():
    if len(sys.argv) != 3:
        print("Usage: vial_generate_defition.py path-to-vial.json path-to-output.h")
        return 1

    with open(sys.argv[1], "r") as inf:
        data = inf.read()

    # minify json
    data = json.dumps(json.loads(data), separators=(',', ':')).strip()

    # compress
    data = lzma.compress(data.encode("utf-8"))

    with open(sys.argv[2], "w") as outf:
        outf.write("#pragma once\n")
        outf.write("static const unsigned char keyboard_definition[] PROGMEM = {")
        arr = ["0x{:02X}".format(b) for b in data]
        outf.write(", ".join(arr))
        outf.write("};\n")

    return 0

if __name__ == "__main__":
    sys.exit(main())
