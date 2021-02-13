"""List the keymaps for a specific keyboard
"""
from milc import cli

import qmk.keymap
from qmk.decorators import automagic_keyboard
from qmk.path import is_keyboard


@cli.argument("-kb", "--keyboard", help="Specify keyboard name. Example: 1upkeyboards/1up60hse")
@cli.subcommand("List the keymaps for a specific keyboard")
@automagic_keyboard
def list_keymaps(cli):
    """List the keymaps for a specific keyboard
    """
    if not is_keyboard(cli.config.list_keymaps.keyboard):
        cli.log.error('Keyboard %s does not exist!', cli.config.list_keymaps.keyboard)
        return False

    for name in qmk.keymap.list_keymaps(cli.config.list_keymaps.keyboard):
        print(name)
