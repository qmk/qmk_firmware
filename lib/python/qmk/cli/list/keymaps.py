"""List the keymaps for a specific keyboard
"""
import os
import re
import glob
from bs4 import UnicodeDammit

from milc import cli

def unicode_text(filename):
    """Returns the contents of filename as a UTF-8 string. Tries to DTRT when it comes to encoding.
    """
    with open(filename, 'rb') as fd:
        text = UnicodeDammit(fd.read())

    if text.contains_replacement_characters:
        log_warning('%s: Could not determine file encoding, some characters were replaced.' % (filename,))

    return text.unicode_markup or ''


def unicode_lines(filename):
    """Returns the contents of filename as a UTF-8 string. Tries to DTRT when it comes to encoding.
    """
    return unicode_text(filename).split('\n')

def parse_rules_mk(keyboard):
    base_path = os.path.join(os.getcwd(), "keyboards", keyboard) + os.path.sep
    rules_mk_path_wildcard = os.path.join(base_path, "**", "rules.mk")
    paths = [path for path in glob.iglob(rules_mk_path_wildcard, recursive=True) if "keymaps" not in path]

    rules_mk = dict()
    for file in paths:
        rules_mk_content = unicode_lines(file)
        parsed_file = dict()
        for line in rules_mk_content:
            found = re.search(r'^\s*(\w+)\s*=\s*((?:\s*\w+)+)', line)
            if found:
                parsed_file[found.group(1)] = found.group(2)
        version = file.replace(base_path, "").replace(os.path.sep, "").replace("rules.mk", "")
        rules_mk[version if version else "base"] = parsed_file
    return rules_mk

def find_keymaps(base_path, name_finder, community = False):
    path_wildcard = os.path.join(base_path, "**", "keymap.c")
    if community:
        paths = [path for path in glob.iglob(path_wildcard, recursive=True)]
    else:
        paths = [path for path in glob.iglob(path_wildcard, recursive=True) if 'keymaps' in path]
    return list(map(name_finder, paths))

@cli.argument('-kb', '--keyboard', help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.subcommand("List the keymaps for a specific keyboard")
def list_keymaps(cli):
    """List the keymaps for a specific keyboard
    """
    # ask for user input if keyboard was not provided in the command line
    keyboard = cli.config.list_keymaps.keyboard if cli.config.list_keymaps.keyboard else input("Keyboard Name: ")

    kb_base_path = os.path.join(os.getcwd(), "keyboards", keyboard) + os.path.sep
    km_find_name = lambda path: path.replace(kb_base_path, keyboard + os.path.sep).replace("/keymaps/", ":").replace(os.path.sep + "keymap.c", "")
    names = find_keymaps(kb_base_path, km_find_name)

    # get all the rules.mk files for the keyboard
    rules_mk = parse_rules_mk(keyboard)

    for version, data in rules_mk.items():
        if "LAYOUTS" in data:
            if version == "base":
                cl_find_name = lambda path: path.replace(cl_base_path, keyboard + ":").replace(os.path.sep + "keymap.c", "")
            else:
                cl_find_name = lambda path: path.replace(cl_base_path, keyboard + os.path.sep + version + ":").replace(os.path.sep + "keymap.c", "")
            for layout in data["LAYOUTS"].split():
                cl_base_path = os.path.join(os.getcwd(), "layouts", "community", layout) + os.path.sep
                names = names + find_keymaps(cl_base_path, cl_find_name, community = True)

    names.sort()

    for name in names:
        # We echo instead of cli.log.info to allow easier piping of this output
        cli.echo(name)
