
import re


def main():
    with open("combos/combos.pretty", "r") as file:
        content = file.read()

    with open("combos.def", "w") as file:
        file.write(re.sub(
            r"COMB\((.+?), *\{(.+?)}\, *(.+?) *\)",
            r"COMB(\1, \3, \2)",
            content
        ))


if __name__ == '__main__':
    main()
