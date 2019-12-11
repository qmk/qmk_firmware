"""This script automates the copying of the default keymap into your own keymap.
"""
import os
import shutil

from milc import cli


@cli.argument('-kb', '--keyboard', help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-km', '--keymap', help='Specify the name for the new keymap directory')
@cli.subcommand('Creates a new keymap for the keyboard of your choosing')
def new_keymap(cli):
    """Creates a new keymap for the keyboard of your choosing.
    """
    # ask for user input if keyboard or keymap was not provided in the command line
    keyboard = cli.config.new_keymap.keyboard if cli.config.new_keymap.keyboard else input("Keyboard Name: ")
    keymap = cli.config.new_keymap.keymap if cli.config.new_keymap.keymap else input("Keymap Name: ")

    # generate keymap paths
    kb_path = os.path.join(os.getcwd(), "keyboards", keyboard)
    keymap_path_default = os.path.join(kb_path, "keymaps/default")
    keymap_path = os.path.join(kb_path, "keymaps/%s" % keymap)

    # check directories
    if not os.path.exists(kb_path):
        cli.log.error('Keyboard %s does not exist!', kb_path)
        exit(1)
    if not os.path.exists(keymap_path_default):
        cli.log.error('Keyboard default %s does not exist!', keymap_path_default)
        exit(1)
    if os.path.exists(keymap_path):
        cli.log.error('Keymap %s already exists!', keymap_path)
        exit(1)

    # create user directory with default keymap files
    shutil.copytree(keymap_path_default, keymap_path, symlinks=True)

    # end message to user
    cli.log.info("%s keymap directory created in: %s", keymap, keymap_path)
    cli.log.info("Compile a firmware with your new keymap by typing: \n" + "qmk compile -kb %s -km %s", keyboard, keymap)
