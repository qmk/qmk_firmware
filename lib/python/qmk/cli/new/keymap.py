"""This script automates the copying of the default keymap into your own keymap.
"""
import shutil
from pathlib import Path

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.keyboard import keyboard_completer, keyboard_folder
from milc import cli


@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-km', '--keymap', help='Specify the name for the new keymap directory')
@cli.subcommand('Creates a new keymap for the keyboard of your choosing')
@automagic_keyboard
@automagic_keymap
def new_keymap(cli):
    """Creates a new keymap for the keyboard of your choosing.
    """
    # ask for user input if keyboard or keymap was not provided in the command line
    keyboard = cli.config.new_keymap.keyboard if cli.config.new_keymap.keyboard else input("Keyboard Name: ")
    keymap = cli.config.new_keymap.keymap if cli.config.new_keymap.keymap else input("Keymap Name: ")

    # generate keymap paths
    kb_path = Path('keyboards') / keyboard
    keymap_path = qmk.path.keymap(keyboard)
    keymap_path_default = keymap_path / 'default'
    keymap_path_new = keymap_path / keymap

    # check directories
    if not kb_path.exists():
        cli.log.error('Keyboard %s does not exist!', kb_path)
        return False

    if not keymap_path_default.exists():
        cli.log.error('Keyboard default %s does not exist!', keymap_path_default)
        return False

    if keymap_path_new.exists():
        cli.log.error('Keymap %s already exists!', keymap_path_new)
        return False

    # create user directory with default keymap files
    shutil.copytree(keymap_path_default, keymap_path_new, symlinks=True)

    # end message to user
    cli.log.info("%s keymap directory created in: %s", keymap, keymap_path_new)
    cli.log.info("Compile a firmware with your new keymap by typing: \n\n\tqmk compile -kb %s -km %s\n", keyboard, keymap)
