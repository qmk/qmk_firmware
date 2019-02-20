#!/usr/bin/env python3

import argparse
import fileinput
import os
import re
import shutil
import subprocess
import sys

from distutils.dir_util import copy_tree

def print_error(message):
    print("[\033[0;91mERROR\033[m] " + message, file=sys.stderr)

def prompt(message, default=""):
    """Ask the user for input, showing the default value in brackets."""
    if default:
        message += f" [{default}]"
    value = input(message + ": ")
    return value or default

def get_git_username():
    """Return the username configured in git config, or None."""
    try:
        return subprocess.check_output(['git', 'config', '--get', 'user.name'], encoding='utf-8').rstrip('\r\n')
    except subprocess.CalledProcessError:
        return None

def copy_template(keyboard_dir, keyboard_name, keyboard_type):
    """Copy the template files to the new keyboard's directory."""
    print("Copying base template...", end='')
    copy_tree('quantum/template/base', keyboard_dir)
    print(" done")

    print(f"Copying {keyboard_type} template...", end='')
    copy_tree(f'quantum/template/{keyboard_type}', keyboard_dir)
    print(" done")

    print("Renaming keyboard files... ", end='')
    shutil.move(f'{keyboard_dir}/template.c', f'{keyboard_dir}/{keyboard_name}.c')
    shutil.move(f'{keyboard_dir}/template.h', f'{keyboard_dir}/{keyboard_name}.h')
    print(" done")

def replace_keyboard_placeholders(keyboard_dir, keyboard_name):
    """Replace all occurrences of "%KEYBOARD%" with the supplied keyboard name."""
    filenames = [
        f'{keyboard_dir}/config.h',
        f'{keyboard_dir}/{keyboard_name}.c',
        f'{keyboard_dir}/readme.md',
        f'{keyboard_dir}/keymaps/default/readme.md'
    ]

    print("Substituting %%KEYBOARD%%...", end='')
    for filename in filenames:
        for line in fileinput.input(filename, inplace=True):
            print(line.replace('%KEYBOARD%', keyboard_name), end='')
    print(" done")

def replace_name_placeholders(keyboard_dir, keyboard_name, name):
    """Replace all occurrences of "REPLACE_WITH_YOUR_NAME" with the supplied name."""
    filenames = [
        f'{keyboard_dir}/config.h',
        f'{keyboard_dir}/{keyboard_name}.c',
        f'{keyboard_dir}/{keyboard_name}.h',
        f'{keyboard_dir}/keymaps/default/config.h',
        f'{keyboard_dir}/keymaps/default/keymap.c'
    ]

    print("Substituting your name...", end='')
    for filename in filenames:
        for line in fileinput.input(filename, inplace=True):
            print(line.replace('REPLACE_WITH_YOUR_NAME', name), end='')
    print(" done")

def keyboard_name_regex(s, pat=re.compile(r'^[a-z0-9_]+$')):
    """Check the allowed characters in keyboard names."""
    if not pat.match(s):
        raise argparse.ArgumentTypeError("Allowed characters are lowercase a-z, 0-9, and underscore (_)")
    return s

if __name__ == '__main__':
    # If we've been started from util/, we want to be in qmk_firmware/
    if os.getcwd().endswith('util'):
        os.chdir('..')

    # Try to make sure we're in the QMK repo
    if 'quantum' not in os.listdir(os.getcwd()):
        print_error("Could not detect the QMK firmware directory!")
        print_error("Are you sure you are in the right place?")
        exit(1)

    keyboard_types = ["avr", "ps2avrgb"]

    parser = argparse.ArgumentParser()
    parser.add_argument("keyboard_name", help="The name of the new keyboard", metavar="keyboard", type=keyboard_name_regex)
    parser.add_argument("--type", help="The type of the new keyboard", dest="keyboard_type", choices=keyboard_types)
    parser.add_argument("--name", help="Your name (default from git config)")
    args = parser.parse_args()

    keyboard_dir = f"keyboards/{args.keyboard_name}"

    if os.path.isdir(keyboard_dir):
        print_error(f"{keyboard_dir} already exists!")
        exit(1)

    print("Generating new QMK keyboard files")
    print()

    # Prompt for keyboard type if not supplied as argument
    if not args.keyboard_type:
        args.keyboard_type = prompt("Keyboard Type", "avr")
        if args.keyboard_type not in keyboard_types:
            raise ValueError(f"Keyboard type must be one of {str(keyboard_types)}")

    # Prompt for your name if not supplied as argument
    if not args.name:
        git_username = get_git_username()
        args.name = prompt("Your Name", git_username)

    print()

    copy_template(keyboard_dir, args.keyboard_name, args.keyboard_type)
    replace_keyboard_placeholders(keyboard_dir, args.keyboard_name)
    if args.name:
        replace_name_placeholders(keyboard_dir, args.keyboard_name, args.name)

    print()
    print(f"Created a new keyboard called {args.keyboard_name}.")
    print()
    print(f"To start working on things, cd into keyboards/{args.keyboard_name},")
    print("or open the directory in your favorite text editor.")
