"""Functions that help us work with files and folders.
"""
import logging
import os
from pathlib import Path

from qmk.errors import NoSuchKeyboardError


def keymap(keyboard):
    """Locate the correct directory for storing a keymap.

    Args:
        keyboard
            The name of the keyboard. Example: clueboard/66/rev3
    """
    keyboard_folder = Path('keyboards') / keyboard

    for i in range(5):
        if (keyboard_folder / 'keymaps').exists():
            return (keyboard_folder / 'keymaps').resolve()

        keyboard_folder = keyboard_folder.parent

    logging.error('Could not find the keymaps directory!')
    raise NoSuchKeyboardError('Could not find keymaps directory for: %s' % keyboard)


def normpath(path):
    """Returns a `pathlib.Path()` object for a given path.

    This will use the path to a file as seen from the directory the script was called from. You should use this to normalize filenames supplied from the command line.
    """
    if path.is_absolute():
        return Path(path)

    return Path(os.environ['ORIG_CWD']) / path
