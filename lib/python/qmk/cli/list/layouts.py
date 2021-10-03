"""List the keymaps for a specific keyboard
"""
from milc import cli

from qmk.decorators import automagic_keyboard
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.info import info_json


@cli.argument("-kb", "--keyboard", type=keyboard_folder, completer=keyboard_completer, help="Specify keyboard name. Example: monarch")
@cli.subcommand("List the layouts for a specific keyboard")
@automagic_keyboard
def list_layouts(cli):
    """List the layouts for a specific keyboard
    """
    info_data = info_json(cli.config.list_layouts.keyboard)
    for name in sorted(info_data.get('community_layouts', [])):
        print(name)
