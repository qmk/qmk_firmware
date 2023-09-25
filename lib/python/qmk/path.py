"""Functions that help us work with files and folders.
"""
import logging
import os
import argparse
from pathlib import Path

from qmk.constants import MAX_KEYBOARD_SUBFOLDERS, QMK_FIRMWARE
from qmk.errors import NoSuchKeyboardError


def is_keyboard(keyboard_name):
    """Returns True if `keyboard_name` is a keyboard we can compile.
    """
    if keyboard_name:
        keyboard_path = QMK_FIRMWARE / 'keyboards' / keyboard_name
        rules_mk = keyboard_path / 'rules.mk'

        return rules_mk.exists()


def under_qmk_firmware():
    """Returns a Path object representing the relative path under qmk_firmware, or None.
    """
    cwd = Path(os.environ['ORIG_CWD'])

    try:
        return cwd.relative_to(QMK_FIRMWARE)
    except ValueError:
        return None


def keyboard(keyboard_name):
    """Returns the path to a keyboard's directory relative to the qmk root.
    """
    return Path('keyboards') / keyboard_name


def keymaps(keyboard_name):
    """Returns all of the `keymaps/` directories for a given keyboard.

    Args:

        keyboard_name
            The name of the keyboard. Example: clueboard/66/rev3
    """
    keyboard_folder = keyboard(keyboard_name)
    found_dirs = []

    for _ in range(MAX_KEYBOARD_SUBFOLDERS):
        if (keyboard_folder / 'keymaps').exists():
            found_dirs.append((keyboard_folder / 'keymaps').resolve())

        keyboard_folder = keyboard_folder.parent

    if len(found_dirs) > 0:
        return found_dirs

    logging.error('Could not find the keymaps directory!')
    raise NoSuchKeyboardError('Could not find keymaps directory for: %s' % keyboard_name)


def keymap(keyboard_name, keymap_name):
    """Locate the directory of a given keymap.

    Args:

        keyboard_name
            The name of the keyboard. Example: clueboard/66/rev3
        keymap_name
            The name of the keymap. Example: default
    """
    for keymap_dir in keymaps(keyboard_name):
        if (keymap_dir / keymap_name).exists():
            return (keymap_dir / keymap_name).resolve()


def normpath(path):
    """Returns a `pathlib.Path()` object for a given path.

    This will use the path to a file as seen from the directory the script was called from. You should use this to normalize filenames supplied from the command line.
    """
    path = Path(path)

    if path.is_absolute():
        return path

    return Path(os.environ['ORIG_CWD']) / path


class FileType(argparse.FileType):
    def __init__(self, *args, **kwargs):
        # Use UTF8 by default for stdin
        if 'encoding' not in kwargs:
            kwargs['encoding'] = 'UTF-8'
        return super().__init__(*args, **kwargs)

    def __call__(self, string):
        """normalize and check exists
            otherwise magic strings like '-' for stdin resolve to bad paths
        """
        norm = normpath(string)
        return norm if norm.exists() else super().__call__(string)
