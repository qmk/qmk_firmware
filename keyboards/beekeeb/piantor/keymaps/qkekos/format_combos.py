
import re
from argparse import ArgumentParser


def main():
    parser = ArgumentParser()
    parser.add_argument(
        "-p", "--path", type=str,
        help="path for the keymap directory"
    )

    cli_args = parser.parse_args()

    with open(f"{cli_args.path}/combos/combos.pretty", "r") as file:
        content = file.read()

    with open(f"{cli_args.path}/combos.def", "w") as file:
        file.write(re.sub(
            r"COMB\((.+?), *\{(.+?)}\, *(.+?) *\)",
            r"COMB(\1, \3, \2)",
            content
        ))


if __name__ == '__main__':
    main()
