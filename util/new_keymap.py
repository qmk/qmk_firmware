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
    """
    Print a message, prefixed with the word "ERROR" in red.
    """
    print("[\033[0;91mERROR\033[m] " + message, file=sys.stderr)
    exit(1)


def get_args(argv):
    """
    Gets script arguments provided in terminal
    """
    # define usage and description
    parser = argparse.ArgumentParser(description=__doc__, usage="./new_keymap.py")
    parser.add_argument("--debug",
                        dest="debug",
                        action="store_true",
                        help="specify to turn on debugging messages")
    return parser.parse_args(argv)


def set_logging(debug=None):
    """
    Sets logging level.

    :debug: bool, True to set logging level to DEBUG & print debug messages
    """
    if debug:
        logging.basicConfig(format="%(levelname)s: %(message)s",
                            level=logging.DEBUG)
        return
    logging.basicConfig(format="%(levelname)s: %(message)s")


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
    if not exists(kb_path):
        print_error(f"{kb_path} does not exist!")
    if not exists(keymap_path_default):
        print_error(f"{keymap_path_default} does not exist!")

    if exists(keymap_path):
        print_error(f"{keymap_path} already exists!")


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
    # set logging level to debug mode if specified
    args = get_args(argv)
    set_logging(args.debug)

    # change current directory up 1 level if in 'util/'
    current_directory = os.path.abspath(os.curdir)
    logging.debug(f"Current directory is {current_directory}")
    if os.path.basename(current_directory) == "util":
        os.chdir("..")
        current_directory = os.path.abspath(os.curdir)
        logging.debug(f"Changed to directory {current_directory}")

    # get keyboard
    keyboard = input("Keyboard Name: ")
    # get username
    username = input("New Username: ")

    # format inputs into directories
    kb_path = os.path.join(current_directory, f"keyboards/{keyboard}")
    keymap_path_default = os.path.join(kb_path, "keymaps/default")
    keymap_path = os.path.join(kb_path, f"keymaps/{username}")
    logging.debug(f"kb_path = {kb_path}\n" +
                  f"keymap_path_default = {keymap_path_default}\n" +
                  f"keymap_path = {keymap_path}\n")

    # check directories
    check_directories(kb_path, keymap_path_default, keymap_path)
    # create user directory with default keymap files
    create_keymap_directory(keymap_path_default, keymap_path)

    # end message to user
    print(f"{username} keymap directory created in: {keymap_path}\n")
    print("Compile a firmware file with your new keymap by typing: \n")
    print(f"make {keyboard}:{username}\n")
    print("from the qmk_firmware directory")


if __name__ == "__main__":
    main()

