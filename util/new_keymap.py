#!/usr/bin/env python3
"""
Script to make a new keymap for a keyboard of your choosing.
This script automates the copying of the default keymap into your own keymap.
"""
import argparse
import logging
import os
import sys

from distutils.dir_util import copy_tree


def print_error(message):
    """Print a message, prefixed with the word "ERROR" in red.
    """
    print("[\033[0;91mERROR\033[m] " + message, file=sys.stderr)
    exit(1)


def get_args(argv):
    """Gets script arguments provided in terminal
    """
    # define usage and description
    parser = argparse.ArgumentParser(description=__doc__, usage="./%(prog)s")
    parser.add_argument("--debug",
                        dest="debug",
                        action="store_true",
                        help="specify to turn on debugging messages")
    return parser.parse_args(argv)


def set_logging(debug=None):
    """Sets logging level.
    """
    if debug:
        logging.basicConfig(format="%(levelname)s: %(message)s",
                            level=logging.DEBUG)
        return
    logging.basicConfig(format="%(levelname)s: %(message)s")


def cd_qmk_root(expected_files):
    """Recursively move up in path until we are at QMK root (which will contain the
    expected files)
    """
    current_directory = os.path.abspath(os.curdir)
    logging.debug("Current directory is " + current_directory)

    # end script with error if at root directory
    if current_directory in {'/', '\\'}:
        print_error("Please execute this script from the qmk_firmware directory")

    # get folders in curdir
    files_found = {name for name in os.listdir(current_directory)}
    # move up one directory if expected files are not found
    if expected_files - files_found:
        os.chdir("..")
        cd_qmk_root(expected_files)

    return os.path.abspath(os.curdir)


def exists(path):
    """Checks if a path exists.
    """
    return os.path.exists(path)


def check_directories(kb_path, keymap_path_default, keymap_path):
    """
    Checks directories.

    The directories to the keyboard & keyboard's default keymap should exist.
    The new keymap directory that will be created should not exist.
    """
    if not exists(kb_path):
        print_error(kb_path + " does not exist!")
    if not exists(keymap_path_default):
        print_error(keymap_path_default + " does not exist!")

    if exists(keymap_path):
        print_error(f"{keymap_path} already exists!")


def create_keymap_directory(keymap_path_default, keymap_path):
    """
    Copies files in the chosen keyboard's keymap/default directory to the
    new keymap directory
    """
    # create new keymap directory
    os.mkdir(keymap_path)
    # recursively copy the chosen keyboard's default keymap
    copy_tree(keymap_path_default, keymap_path)


def main(argv=sys.argv[1:]):
    # set logging level to debug mode if specified
    args = get_args(argv)
    set_logging(args.debug)


    # recursively change current directory up 1 level until at QMK root
    qmk_root_dirs = {'drivers', 'util', 'tests', 'keyboards'}
    current_directory = cd_qmk_root(qmk_root_dirs)

    # get keyboard
    keyboard = input("Keyboard Name: ")
    # get username
    username = input("New Username: ")

    # format inputs into directories
    kb_path = os.path.join(current_directory, "keyboards/" + keyboard)
    keymap_path_default = os.path.join(kb_path, "keymaps/default")
    keymap_path = os.path.join(kb_path, "keymaps/" + username)
    logging.debug("kb_path = {}".format(kb_path))
    logging.debug("keymap_path_default = {}".format(keymap_path_default))
    logging.debug("keymap_path = {}".format(keymap_path))

    # check directories
    check_directories(kb_path, keymap_path_default, keymap_path)
    # create user directory with default keymap files
    create_keymap_directory(keymap_path_default, keymap_path)

    # end message to user
    print("{} keymap directory created in: {}\n".format(username, keymap_path))
    print("Compile a firmware file with your new keymap by typing: \n")
    print("make {}:{}\n".format(keyboard, username))
    print("from the qmk_firmware directory")


if __name__ == "__main__":
    main()
