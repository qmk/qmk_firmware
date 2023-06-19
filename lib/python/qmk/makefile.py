""" Functions for working with Makefiles
"""
from pathlib import Path


def parse_rules_mk_file(file, rules_mk=None):
    """Turn a rules.mk file into a dictionary.

    Args:
        file: path to the rules.mk file
        rules_mk: already parsed rules.mk the new file should be merged with

    Returns:
        a dictionary with the file's content
    """
    if not rules_mk:
        rules_mk = {}

    file = Path(file)
    if file.exists():
        rules_mk_lines = file.read_text(encoding='utf-8').split("\n")

        for line in rules_mk_lines:
            # Filter out comments
            if line.strip().startswith("#"):
                continue

            # Strip in-line comments
            if '#' in line:
                line = line[:line.index('#')].strip()

            if '=' in line:
                # Append
                if '+=' in line:
                    key, value = line.split('+=', 1)
                    if key.strip() not in rules_mk:
                        rules_mk[key.strip()] = value.strip()
                    else:
                        rules_mk[key.strip()] += ' ' + value.strip()
                # Set if absent
                elif "?=" in line:
                    key, value = line.split('?=', 1)
                    if key.strip() not in rules_mk:
                        rules_mk[key.strip()] = value.strip()
                else:
                    if ":=" in line:
                        line.replace(":", "")
                    key, value = line.split('=', 1)
                    rules_mk[key.strip()] = value.strip()

    return rules_mk
