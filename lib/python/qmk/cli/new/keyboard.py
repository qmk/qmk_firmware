"""This script automates creating the files necessary for a new QMK keyboard.
"""
import os
import shutil

from milc import cli


@cli.argument('-kb', '--keyboard', help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-mcu', '--microcontroller', help='Specify the microcontroller used for the keyboard.')
@cli.subcommand('Creates a new keyboard project.')
def new_keyboard(cli):
    """Creates a new keyboard project.
    """
    # ask for user input if keyboard or keymap was not provided in the command line
    keyboard = input("Keyboard Name: ")
    microcontroller = input("Microcontroller: ")

    # generate keymap paths
    kb_path = os.path.join(os.getcwd(), "keyboards", keyboard)
    template_base_path = os.path.join(os.getcwd(), "quantum/template/base")

    # check directories
    if os.path.exists(kb_path):
        cli.log.error('Keyboard %s already exists!', kb_path)
        exit(1)

    # create user directory with default keymap files
    shutil.copytree(template_base_path, kb_path, symlinks=True)

    # end message to user
    cli.log.info("%s keyboard directory created in: %s", keyboard, kb_path)
    cli.log.info("Compile a firmware with your new keymap by typing: \n" + "qmk compile -kb %s -km default", keyboard)
