"""List the keymaps for a specific keyboard
"""
from milc import cli

import qmk.keymap
from qmk.decorators import automagic_keyboard
from qmk.keyboard import keyboard_completer, keyboard_folder


@cli.argument("-kb", "--keyboard", type=keyboard_folder, completer=keyboard_completer, help="Specify keyboard name. Example: 1upkeyboards/1up60hse")
@cli.subcommand("List the keymaps for a specific keyboard")
@automagic_keyboard
def list_keymaps(cli):
    """List the keymaps for a specific keyboard
    """
    for name in qmk.keymap.list_keymaps(cli.config.list_keymaps.keyboard):
        print(name)
