#!/usr/bin/env python3
import secrets


def main():
    print("#define VIAL_KEYBOARD_UID {{{}}}".format(
        ", ".join(["0x{:02X}".format(x) for x in secrets.token_bytes(8)])
    ))


if __name__ == "__main__":
    main()
