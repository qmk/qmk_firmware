"""This script automates the generation of a new keyboard directory.
"""
import os
import shutil

from distutils.dir_util import copy_tree
from datetime import datetime
from milc import cli


def replace_files(filenames, search, replace):
    """Replaces keywords across multiple files
    """
    for filename in filenames:
        with open(filename, 'r') as file:
            contents = file.read()

        contents = contents.replace(search, replace)

        with open(filename, 'w') as file:
            file.write(contents)


@cli.argument('-kb', '--keyboard', help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.argument('-t', '--type', help='Specify keyboard type. Valid Options: avr or ps2avrgb')
@cli.argument('-u', '--username', help='Specify username. Example: skullydazed')
@cli.subcommand('Creates a new keyboard of your choosing')
def new_keyboard(cli):
    """Creates a new keyboard of your choosing.
    """
    # ask for user input if keyboard, type, or username was not provided in the command line
    keyboard = cli.config.new_keyboard.keyboard if cli.config.new_keyboard.keyboard else input("Keyboard Name: ")
    keyboard_type = cli.config.new_keyboard.type if cli.config.new_keyboard.type else input("Keyboard Type: ")
    username = cli.config.new_keyboard.username if cli.config.new_keyboard.username else input("Username: ")

    # generate keyboard paths
    kb_path = os.path.join(os.getcwd(), "keyboards", keyboard)
    kb_path_base = os.path.join(os.getcwd(), "quantum/template/base")
    kb_path_type = os.path.join(os.getcwd(), "quantum/template", keyboard_type)

    # check keyboard type
    valid_types = ["avr", "ps2avrgb"]
    if keyboard_type not in valid_types:
        cli.log.error('Keyboard type %s must be one of %s!', keyboard_type, valid_types)
        exit(1)

    # check directories
    if os.path.exists(kb_path):
        cli.log.error('Keyboard %s already exists!', kb_path)
        exit(1)
    if not os.path.exists(kb_path_base):
        cli.log.error('Keyboard default %s does not exist!', kb_path_base)
        exit(1)
    if not os.path.exists(kb_path_type):
        cli.log.error('Keyboard type %s does not exist!', kb_path_type)
        exit(1)

    # create user directory with mix of keyboard base and keyboard type
    copy_tree(kb_path_base, kb_path, preserve_symlinks=1)
    copy_tree(kb_path_type, kb_path, preserve_symlinks=1)

    # rename template files to keyboard
    shutil.move(os.path.join(kb_path, "template.c"), os.path.join(kb_path, "%s.c" % keyboard))
    shutil.move(os.path.join(kb_path, "template.h"), os.path.join(kb_path, "%s.h" % keyboard))

    # replace year placeholders
    replace_files([
        os.path.join(kb_path, "config.h"),
        os.path.join(kb_path, "%s.c" % keyboard),
        os.path.join(kb_path, "%s.h" % keyboard),
        os.path.join(kb_path, "keymaps/default/config.h"),
        os.path.join(kb_path, "keymaps/default/keymap.c"),
    ], "%YEAR%", str(datetime.now().year))

    # replace keyboard name placeholders
    replace_files([
        os.path.join(kb_path, "config.h"),
        os.path.join(kb_path, "readme.md"),
        os.path.join(kb_path, "%s.c" % keyboard),
        os.path.join(kb_path, "keymaps/default/readme.md"),
    ], "%KEYBOARD%", keyboard)

    # replace username placeholders
    replace_files([
        os.path.join(kb_path, "config.h"),
        os.path.join(kb_path, "readme.md"),
        os.path.join(kb_path, "%s.c" % keyboard),
        os.path.join(kb_path, "%s.h" % keyboard),
        os.path.join(kb_path, "keymaps/default/config.h"),
        os.path.join(kb_path, "keymaps/default/keymap.c"),
    ], "%YOUR_NAME%", username)

    # end message to user
    cli.log.info("Created a new keyboard called %s\n", keyboard)
    cli.log.info("To start working on things, cd into keyboards/%s,", keyboard)
    cli.log.info("or open the directory in your favourite text editor.")
