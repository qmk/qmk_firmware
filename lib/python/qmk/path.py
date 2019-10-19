"""Functions that help us work with files and folders.
"""
import logging
import os
from pkgutil import walk_packages

from qmk.errors import NoSuchKeyboardError


def keymap(keyboard):
    """Locate the correct directory for storing a keymap.

    Args:
        keyboard
            The name of the keyboard. Example: clueboard/66/rev3
    """
    for directory in ['.', '..', '../..', '../../..', '../../../..', '../../../../..']:
        basepath = os.path.normpath(os.path.join('keyboards', keyboard, directory, 'keymaps'))

        if os.path.exists(basepath):
            return basepath

    logging.error('Could not find keymaps directory!')
    raise NoSuchKeyboardError('Could not find keymaps directory for: %s' % keyboard)


def normpath(path):
    """Returns the fully resolved absolute path to a file.

    This function will return the absolute path to a file as seen from the
    directory the script was called from.
    """
    if path and path[0] == '/':
        return os.path.normpath(path)

    return os.path.normpath(os.path.join(os.environ['ORIG_CWD'], path))
