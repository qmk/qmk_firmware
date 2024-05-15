
import re
import json

prefix = "-" * 36
postfix = "-" * 39


def main():
    with open("./magic.txt", "r") as file:
        file_content = file.read()

    file_content = file_content.replace("//REGEX_END", "")

    raw_blocks = collect_blocks(file_content)
    rule_counts = get_rule_counts(raw_blocks)

    block_headers = collect_block_headers(file_content)

    dictionary = dict(zip(block_headers, rule_counts))
    print(json.dumps(dictionary, indent=4))

    max_key = max(dictionary.keys(), key=lambda x: dictionary[x])
    print(f"Max: {max_key}: {dictionary[max_key]}")


def collect_block_headers(file: str) -> list[str]:
    return re.findall(f"// {prefix}(.){postfix}", file)


def collect_blocks(file: str) -> list[str]:
    return re.split(f"// {prefix}.{postfix}", file)[1:]


def get_rule_counts(blocks: list[str]) -> list[int]:
    return [get_rule_count(block) for block in blocks]


def get_rule_count(block: str) -> int:
    block = block.strip()
    return len([line for line in block.split("\n") if line])


if __name__ == "__main__":
    main()
