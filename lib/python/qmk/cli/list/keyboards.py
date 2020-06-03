"""List the keyboards currently defined within QMK
"""
# We avoid pathlib here because this is performance critical code.
import os
import glob

from milc import cli

BASE_PATH = os.path.join(os.getcwd(), "keyboards") + os.path.sep
KB_WILDCARD = os.path.join(BASE_PATH, "**", "rules.mk")


def find_name(path):
    """Determine the keyboard name by stripping off the base_path and rules.mk.
    """
    return path.replace(BASE_PATH, "").replace(os.path.sep + "rules.mk", "")


@cli.subcommand("List the keyboards currently defined within QMK")
def list_keyboards(cli):
    """List the keyboards currently defined within QMK
    """
    # find everywhere we have rules.mk where keymaps isn't in the path
    paths = [path for path in glob.iglob(KB_WILDCARD, recursive=True) if 'keymaps' not in path]

    # Extract the keyboard name from the path and print it
    for keyboard_name in sorted(map(find_name, paths)):
        print(keyboard_name)
