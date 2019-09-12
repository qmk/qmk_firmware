"""This script automates the copying of the default keymap into your own keymap.
"""
import os
import shutil

from milc import cli


@cli.argument('-k', '--keyboard', help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-u', '--username', help='Specify any name for the new keymap directory')
@cli.entrypoint('Creates a new keymap for the keyboard of your choosing')
def main(cli):
    """Creates a new keymap for the keyboard of your choosing.
    """
    # ask for user input if keyboard or username was not provided in the command line
    keyboard = cli.config.general.keyboard if cli.config.general.keyboard else input("Keyboard Name: ")
    username = cli.config.general.username if cli.config.general.username else input("Username: ")

    # generate keymap paths
    kb_path = os.path.join(os.getcwd(), "keyboards", keyboard)
    keymap_path_default = os.path.join(kb_path, "keymaps/default")
    keymap_path = os.path.join(kb_path, "keymaps/%s" % username)

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
    cli.log.info("%s keymap directory created in: %s\n" +
                 "Compile a firmware file with your new keymap by typing: \n" +
                 "qmk compile -kb %s -km %s", username, keymap_path, keyboard, username)
