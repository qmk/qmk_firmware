"""Functions that help us work with files and folders.
"""
import logging
import os
from distutils.dir_util import copy_tree

from qmk.errors import NoSuchKeyboardError, DirectoryError


def keymap(keyboard):
    """Locate the correct directory for storing a keymap.

    Args:
        keyboard
            The name of the keyboard. Example: clueboard/66/rev3
    """
    for directory in ['.', '..', '../..', '../../..', '../../../..', '../../../../..']:
        basepath = os.path.normpath(os.path.join(directory, 'keyboards', keyboard, 'keymaps'))

        if os.path.exists(basepath):
            return basepath

    logging.error('Could not find keymaps directory!')
    raise NoSuchKeyboardError('Could not find keymaps directory for: %s' % keyboard)


def check_directories(*directories, exist=True, dont_raise=False):
    """Checks existence of all directories entered.
    Specify exist as False to verify path should not exist
    Args:
        *directories
            Path(s) to verify existence
        exist
            bool that determines if function should confirm paths exists (default) or
            should not exist (False). Is optional.
        dont_raise
            bool that determines if function should raise an error.
            Default behavior is to raise an error unless set to True
    """
    if exist:
        error_message = 'Could not find directory: %s'
    else:
        error_message = 'Did not expected to find directory: %s'

    error_paths = []
    for path in directories:
        if exist and not os.path.exists(path):
            logging.error(path + " does not exist!")
            error_paths.append(path)
        elif not exist and os.path.exists(path):
            logging.error(path + " should not exist!")
            error_paths.append(path)

    if error_paths and not dont_raise:
        raise DirectoryError(error_message % error_paths)

    return False if error_paths else True


def create_keymap_directory(default_keymap_directory, new_keymap_directory):
    """Copies files in an existing keyboard's keymap/default directory to the
    new keymap directory

    Args:
        default_keymap_directory
            The normpath to the default keymap directory.
        new_keymap_directory
            The normpath where the new keymap directory will be created.

    """
    # create new keymap directory
    os.mkdir(new_keymap_directory)
    # recursively copy the chosen keyboard's default keymap
    copy_tree(default_keymap_directory, new_keymap_directory)


def normpath(path):
    """Returns the fully resolved absolute path to a file.

    This function will return the absolute path to a file as seen from the
    directory the script was called from.
    """
    if path and path[0] == '/':
        return os.path.normpath(path)

    return os.path.normpath(os.path.join(os.environ['ORIG_CWD'], path))
