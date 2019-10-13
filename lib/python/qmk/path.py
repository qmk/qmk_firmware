"""Functions that help us work with files and folders.
"""
import logging
import os

from qmk.errors import NoSuchKeyboardError

from bs4 import UnicodeDammit

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

def unicode_text(filename):
    """Returns the contents of filename as a UTF-8 string. Tries to DTRT when it comes to encoding.
    """
    with open(filename, "rb") as fd:
        text = UnicodeDammit(fd.read())

    if text.contains_replacement_characters:
        log_warning("%s: Could not determine file encoding, some characters were replaced." % (filename,))

    return text.unicode_markup or ""


def unicode_lines(filename):
    """Returns the contents of filename as a UTF-8 string. Tries to DTRT when it comes to encoding.
    """
    return unicode_text(filename).split("\n")
