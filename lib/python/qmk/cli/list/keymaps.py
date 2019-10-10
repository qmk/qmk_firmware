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
    with open(filename, "rb") as fd:
        text = UnicodeDammit(fd.read())

    if text.contains_replacement_characters:
        log_warning("%s: Could not determine file encoding, some characters were replaced." % (filename,))

    return text.unicode_markup or ""


def unicode_lines(filename):
    """Returns the contents of filename as a UTF-8 string. Tries to DTRT when it comes to encoding.
    """
    return unicode_text(filename).split("\n")

def parse_rules_mk(keyboard, revision = ""):
    base_path = os.path.join(os.getcwd(), "keyboards", keyboard) + os.path.sep
    rules_mk_path_wildcard = os.path.join(base_path, "**", "rules.mk")
    rules_mk_regex = re.compile(r"^" + base_path + "(?:" + revision + os.path.sep + ")?rules.mk")
    paths = [path for path in glob.iglob(rules_mk_path_wildcard, recursive = True) if rules_mk_regex.search(path)]

    rules_mk = dict()
    config_regex = re.compile(r"^\s*(\S+)\s*=\s*((?:\s*\S+)+)")
    for file_path in paths:
        rules_mk_content = unicode_lines(file_path)
        parsed_file = dict()
        for line in rules_mk_content:
            found = config_regex.search(line)
            if found:
                parsed_file[found.group(1)] = found.group(2)
        version = file_path.replace(base_path, "").replace(os.path.sep, "").replace("rules.mk", "")
        rules_mk[version if version else "base"] = parsed_file
    return rules_mk

def find_keymaps(base_path, revision = "", community = False):
    path_wildcard = os.path.join(base_path, "**", "keymap.c")
    if community:
        path_regex = re.compile(r"^" + re.escape(base_path) + "(\S+)" + os.path.sep + "keymap\.c")
        names = [revision + os.path.sep + path_regex.sub(lambda name: name.group(1), path) for path in glob.iglob(path_wildcard, recursive = True)]
    else:
        path_regex = re.compile(r"^" + re.escape(base_path) + "(?:" + re.escape(revision) + os.path.sep + ")?keymaps" + os.path.sep + "(\S+)" + os.path.sep + "keymap\.c")
        names = [revision + os.path.sep + path_regex.sub(lambda name: name.group(1), path) if revision else path_regex.sub(lambda name: name.group(1), path) for path in glob.iglob(path_wildcard, recursive = True) if path_regex.search(path)]
    return names

@cli.argument("-kb", "--keyboard", help="Specify keyboard name. Example: 1upkeyboards/1up60hse")
@cli.argument("-rv", "--revision", help="Specify the revison name. Example: rev6")
@cli.subcommand("List the keymaps for a specific keyboard")
def list_keymaps(cli):
    """List the keymaps for a specific keyboard
    """
    # ask for user input if keyboard was not provided in the command line
    keyboard = cli.config.list_keymaps.keyboard if cli.config.list_keymaps.keyboard else input("Keyboard Name: ")
    revision = cli.config.list_keymaps.revision if cli.config.list_keymaps.revision else ""

    # get all the rules.mk files for the keyboard
    rules_mk = parse_rules_mk(keyboard, revision)

    if "base" in rules_mk or revision:
        keyboard_name = keyboard + os.path.sep + revision
        kb_base_path = os.path.join(os.getcwd(), "keyboards", keyboard) + os.path.sep
        names = find_keymaps(kb_base_path, revision)
    else:
        names = list()

    for rev, data in rules_mk.items():
        if "LAYOUTS" in data:
            for layout in data["LAYOUTS"].split():
                cl_base_path = os.path.join(os.getcwd(), "layouts", "community", layout) + os.path.sep
                names = names + find_keymaps(cl_base_path, rev, community = True)

    names.sort()

    for name in names:
        # We echo instead of cli.log.info to allow easier piping of this output
        cli.echo(keyboard + os.path.sep + name)
