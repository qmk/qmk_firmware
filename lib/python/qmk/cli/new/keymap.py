#!/usr/bin/env python
"""
This script automates the copying of the default keymap into your own keymap.
"""
import os
import sys

# TODO (orngshdw): need to figure out where this script will be called from to prevent
#   the "ModuleNotFoundError: No module named 'milc'" error
#   am executing file from the lib/python/
path = os.path.abspath(".")
sys.path.append(path)

from milc import cli
from qmk.path import keymap, check_directories, create_keymap_directory


# TODO(orngshdw): add debugging code if needed:
#   @cli.argument('--debug', dest='debug', action='store_true', help='specify to turn on debugging messages')
@cli.entrypoint('Create a new keymap.c from the default keyboard of your choosing')
def main(cli):

    # get keyboard
    keyboard = input("Keyboard Name: ")
    # get username
    username = input("New Username: ")

    # generate keymap paths
    kb_path = os.path.abspath(keymap(keyboard))
    print(kb_path)
    keymap_path_default = kb_path + "/default"
    keymap_path = kb_path + "/" + username

    # check directories
    check_directories(kb_path, keymap_path_default)
    check_directories(keymap_path, exist=False)

    # create user directory with default keymap files
    create_keymap_directory(keymap_path_default, keymap_path)

    # end message to user
    print("%s keymap directory created in: %s\n" % (
        username,
        keymap_path,
    ))
    print("Compile a firmware file with your new keymap by typing: \n")
    print("make %s:%s\n" % (
        keyboard,
        username,
    ))
    print("from the qmk_firmware directory")


if __name__ == '__main__':
    cli()

# TODO (orngshdw): delete before merging to master
#   for reference until we decide if we need logging/debugging for this script
""" 
def get_args(argv): #Gets script arguments provided in terminal
    # define usage and description
    parser = argparse.ArgumentParser(description=__doc__, usage="./%(prog)s")
    parser.add_argument("--debug",
                        dest="debug",
                        action="store_true",
                        help="specify to turn on debugging messages")
    return parser.parse_args(argv)

def set_logging(debug=None): # Sets logging level.
    if debug:
        logging.basicConfig(format="%(levelname)s: %(message)s",
                level=logging.DEBUG)
        return
    logging.basicConfig(format="%(levelname)s: %(message)s")
"""
