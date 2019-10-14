""" Functions for working with Makefiles
"""
import os
import glob
import re

import qmk.path
from qmk.errors import NoSuchKeyboardError

def parse_rules_mk(file_path):
    """ Parse a rules.mk file

    Args:
        file_path: path to the rules.mk file

    Returns:
        a dictionary with the file's content
    """
    # regex to match lines uncommented lines and get the data
    # group(1) = option's name
    # group(2) = operator (eg.: '=', '+=')
    # group(3) = value(s)
    rules_mk_regex = re.compile(r"^\s*(\w+)\s*([\?\:\+\-]?=)\s*(\S.*?)(?=\s*(\#|$))")
    mk_content = qmk.path.unicode_lines(file_path)
    parsed_file = dict()
    for line in mk_content:
        found = rules_mk_regex.search(line)
        if found:
            parsed_file[found.group(1)] = dict(operator = found.group(2), value = found.group(3))
    return parsed_file

def merge_rules_mk_files(base, revision):
    """ Merge a keyboard revision's rules.mk file with
    the 'base' rules.mk file

    Args:
        base: the base rules.mk file's content as dictionary
        revision: the revision's rules.mk file's content as dictionary

    Returns:
        a dictionary with the merged content
    """
    return {**base, **revision}

def get_rules_mk(keyboard, revision = ""):
    """ Get a rules.mk for a keyboard

    Args:
        keyboard: name of the keyboard
        revision: revision of the keyboard

    Returns:
        a dictionary with the content of the rules.mk file
    """
    base_path = os.path.join(os.getcwd(), "keyboards", keyboard) + os.path.sep
    rules_mk = dict()
    if os.path.exists(base_path + os.path.sep + revision):
        rules_mk_path_wildcard = os.path.join(base_path, "**", "rules.mk")
        rules_mk_regex = re.compile(r"^" + base_path + "(?:" + revision + os.path.sep + ")?rules.mk")
        paths = [path for path in glob.iglob(rules_mk_path_wildcard, recursive = True) if rules_mk_regex.search(path)]
        for file_path in paths:
            rules_mk[revision if revision in file_path else "base"] = parse_rules_mk(file_path)
    else:
        raise NoSuchKeyboardError("The requested keyboard and/or revision does not exist.")

    # if the base or the revision directory does not contain a rules.mk
    if len(rules_mk) == 1:
        rules_mk = rules_mk[revision]
    # if both directories contain rules.mk files
    elif len(rules_mk) == 2:
        rules_mk = merge_rules_mk_files(rules_mk["base"], rules_mk[revision])
    return rules_mk
