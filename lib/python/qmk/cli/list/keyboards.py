"""List the keyboards currently defined within QMK
"""
from milc import cli

import qmk.keyboard


@cli.subcommand("List the keyboards currently defined within QMK")
def list_keyboards(cli):
    """List the keyboards currently defined within QMK
    """
    for keyboard_name in qmk.keyboard.list_keyboards():
        print(keyboard_name)
