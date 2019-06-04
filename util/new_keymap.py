#!/usr/bin/env python
"""
Script to make a new keymap for a keyboard of your choosing.
This script automates the copying of the default keymap into your own keymap.
"""
import argparse
import logging
import os
import sys

from distutils.dir_util import copy_tree


usage_message = "./new_keymap.py <keyboard_path> <username>\n" + \
                "Example: ./new_keymap.py 1upkeyboards/1up60hse yourname"


def get_args(argv):
    """
    Gets script arguments provided in terminal
    """
    # define usage and description
    parser = argparse.ArgumentParser(description=__doc__, usage=usage_message)
    parser.add_argument("input", type=str, nargs=2,
                        help="specified keyboard & username. See usage above")
    parser.add_argument("--debug", dest="debug", action="store_true",
                        help="specify to turn on debugging messages")

    return parser.parse_args(argv)


def set_logs(debug=None):
    """
    Sets logging level.

    :debug: bool, True to set logging level to DEBUG & print debug messages
    """
    if debug:
        logging.basicConfig(format="%(levelname)s: %(message)s", level=logging.DEBUG)


def exists(path):
    """
    Checks if a path exists.

    :return: True if path exists, else False
    """
    return os.path.exists(path)


def check_directories(kb_path, keymap_path_default, keymap_path):
    """
    Checks directories.

    The directories to the keyboard & keyboard's default keymap should exist.
    The new keymap directory that will be created should not exist.

    :kb_path: str, keyboard directory
    :keymap_path_default: str, default keymap directory for the keyboard
    :keymap_path: str, new keymap directory that will be created
    """
    assert exists(kb_path), "Error! {} does not exist!".format(kb_path)
    assert exists(keymap_path_default), \
        "Error! {} does not exist!".format(keymap_path_default)

    assert exists(keymap_path) is False, \
        "Error! {} already exists!".format(keymap_path)


def create_keymap_directory(keymap_path_default, keymap_path):
    """
    Copies files in the chosen keyboard's keymap/default directory
    to the new keymap directory

    :keymap_path_default: str, default keymap directory for the keyboard
    :keymap_path: str, new keymap directory that will be created
    """
    # create new keymap directory
    os.mkdir(keymap_path)
    # recursively copy the chosen keyboard's default keymap
    copy_tree(keymap_path_default, keymap_path)


def main(argv=sys.argv[1:]):
    # get script args
    args = get_args(argv)

    # set logging level to debug mode if specified
    set_logs(args.debug)

    logging.debug("script args = {}".format(args))

    # change current directory up 1 level if in 'util/'
    current_directory = os.path.abspath(os.curdir)
    logging.debug("Current directory is {}".format(current_directory))
    if os.path.basename(current_directory) == "util":
        os.chdir("..")
        current_directory = os.path.abspath(os.curdir)
        logging.debug("Changed to directory {}".format(current_directory))

    # format inputs into directories
    kb_path = os.path.join(current_directory, "keyboards/{}".format(args.input[0]))
    keymap_path_default = os.path.join(kb_path, "keymaps/default")
    keymap_path = os.path.join(kb_path, "keymaps/{}".format(args.input[1]))
    logging.debug(
        "kb_path = {}".format(kb_path) +
        "keymap_path_default = {}".format(keymap_path_default) +
        "keymap_path = {}".format(keymap_path)
    )

    # check directories
    check_directories(kb_path, keymap_path_default, keymap_path)
    # create user directory with default keymap files
    create_keymap_directory(keymap_path_default, keymap_path)

    # end message to user
    print("{} keymap directory created in: {}\n".format(args.input[1], kb_path))
    print("Compile a firmware file with your new keymap by typing: \n")
    print("make {}:{}\n".format(args.input[0], args.input[1]))
    print("from the qmk_firmware directory")


if __name__ == "__main__":
    # maintain similar new_keymap.sh behavior when called without arguments
    if not len(sys.argv[1:]):
        print("Usage: " + usage_message)
        sys.exit()
        
    main()

