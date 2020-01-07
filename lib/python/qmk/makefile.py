""" Functions for working with Makefiles
"""
import os

import qmk.path
from qmk.errors import NoSuchKeyboardError


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

    if os.path.exists(file):
        rules_mk_lines = qmk.path.file_lines(file)

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


def get_rules_mk(keyboard):
    """ Get a rules.mk for a keyboard

    Args:
        keyboard: name of the keyboard

    Raises:
        NoSuchKeyboardError: when the keyboard does not exists

    Returns:
        a dictionary with the content of the rules.mk file
    """
    # Start with qmk_firmware/keyboards
    kb_path = os.path.join(os.getcwd(), "keyboards")
    # walk down the directory tree
    # and collect all rules.mk files
    if os.path.exists(os.path.join(kb_path, keyboard)):
        rules_mk = dict()
        for directory in keyboard.split(os.path.sep):
            kb_path = os.path.join(kb_path, directory)
            rules_mk_path = os.path.join(kb_path, "rules.mk")
            if os.path.exists(rules_mk_path):
                rules_mk = parse_rules_mk_file(rules_mk_path, rules_mk)
    else:
        raise NoSuchKeyboardError("The requested keyboard and/or revision does not exist.")

    return rules_mk
