"""List the keyboards currently defined within QMK
"""
import os
import re
import glob

from milc import cli

@cli.subcommand("List the keyboards currently defined within QMK")
def list_keyboards(cli):
    """List the keyboards currently defined within QMK
    """

    base_path = os.path.join(os.getcwd(), "keyboards") + os.path.sep
    kb_path_wildcard = os.path.join(base_path, "**", "rules.mk")

    # find everywhere we have rules.mk where keymaps isn't in the path
    paths = [path for path in glob.iglob(kb_path_wildcard, recursive=True) if 'keymaps' not in path]

    # strip the keyboard directory path prefix and rules.mk suffix and alphabetize
    find_name = lambda path: path.replace(base_path, "").replace(os.path.sep + "rules.mk", "")
    names = sorted(map(find_name, paths))

    for name in names:
        # We echo instead of cli.log.info to allow easier piping of this output
        cli.echo(name)
