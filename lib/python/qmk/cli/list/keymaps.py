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

    rules_mk = list()
    for file in paths:
        rules_mk_content = unicode_lines(file)
        parsed_file = dict()
        for line in rules_mk_content:
            found = re.search(r'^\s*(\w+)\s*=\s*((?:\s*\w+)+)', line)
            if found:
                parsed_file[found.group(1)] = found.group(2)
        rules_mk.append(parsed_file)
    return rules_mk

@cli.argument('-kb', '--keyboard', help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.subcommand("List the keymaps for a specific keyboard")
def list_keymaps(cli):
    """List the keymaps for a specific keyboard
    """
    # ask for user input if keyboard was not provided in the command line
    keyboard = cli.config.list_keymaps.keyboard if cli.config.list_keymaps.keyboard else input("Keyboard Name: ")

    kb_base_path = os.path.join(os.getcwd(), "keyboards", keyboard) + os.path.sep
    km_path_wildcard = os.path.join(kb_base_path, "**", "keymap.c")

    # find everywhere we have rules.mk where keymaps isn't in the path
    km_paths = [path for path in glob.iglob(km_path_wildcard, recursive=True) if 'keymaps' in path]

    # replace the keyboard directory's path prefix with the keyboard's name and remove the keymap.c suffix
    km_find_name = lambda path: path.replace(kb_base_path, keyboard + os.path.sep).replace("/keymaps/", ":").replace(os.path.sep + "keymap.c", "")
    names = list(map(km_find_name, km_paths))

    # get all the rules.mk files for the keyboard
    rules_mk = parse_rules_mk(keyboard)

    # find all the supported layouts
    all_supported_layouts = set()
    for version in rules_mk:
        if "LAYOUTS" in version:
            for layout in version["LAYOUTS"].split():
                all_supported_layouts.add(layout)

    for layout in all_supported_layouts:
        cl_base_path = os.path.join(os.getcwd(), "layouts", "community", layout) + os.path.sep
        cl_path_wildcard = os.path.join(cl_base_path, "**", "keymap.c")
        # find all the keymap.c files under the community layouts
        cl_paths = [path for path in glob.iglob(cl_path_wildcard, recursive=True)]
        # replace the community layouts directory's path with the keyboard's name and remove the keymap.c suffix
        cl_find_name = lambda path: path.replace(cl_base_path, keyboard + ":").replace(os.path.sep + "keymap.c", "")
        names = names + list(map(cl_find_name, cl_paths))

    names.sort()

    for name in names:
        # We echo instead of cli.log.info to allow easier piping of this output
        cli.echo(name)
