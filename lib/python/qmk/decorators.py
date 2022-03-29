"""Helpful decorators that subcommands can use.
"""
import functools
from time import monotonic

from milc import cli

from qmk.keyboard import find_keyboard_from_dir
from qmk.keymap import find_keymap_from_dir


def automagic_keyboard(func):
    """Sets `cli.config.<subcommand>.keyboard` based on environment.

    This will rewrite cli.config.<subcommand>.keyboard if the user did not pass `--keyboard` and the directory they are currently in is a keyboard or keymap directory.
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # Ensure that `--keyboard` was not passed and CWD is under `qmk_firmware/keyboards`
        if cli.config_source[cli._subcommand.__name__]['keyboard'] != 'argument':
            keyboard = find_keyboard_from_dir()

            if keyboard:
                cli.config[cli._subcommand.__name__]['keyboard'] = keyboard
                cli.config_source[cli._subcommand.__name__]['keyboard'] = 'keyboard_directory'

        return func(*args, **kwargs)

    return wrapper


def automagic_keymap(func):
    """Sets `cli.config.<subcommand>.keymap` based on environment.

    This will rewrite cli.config.<subcommand>.keymap if the user did not pass `--keymap` and the directory they are currently in is a keymap, layout, or user directory.
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # Ensure that `--keymap` was not passed and that we're under `qmk_firmware`
        if cli.config_source[cli._subcommand.__name__]['keymap'] != 'argument':
            keymap_name, keymap_type = find_keymap_from_dir()

            if keymap_name:
                cli.config[cli._subcommand.__name__]['keymap'] = keymap_name
                cli.config_source[cli._subcommand.__name__]['keymap'] = keymap_type

        return func(*args, **kwargs)

    return wrapper


def lru_cache(timeout=10, maxsize=128, typed=False):
    """Least Recently Used Cache- cache the result of a function.

    Args:

        timeout
            How many seconds to cache results for.

        maxsize
            The maximum size of the cache in bytes

        typed
            When `True` argument types will be taken into consideration, for example `3` and `3.0` will be treated as different keys.
    """
    def wrapper_cache(func):
        func = functools.lru_cache(maxsize=maxsize, typed=typed)(func)
        func.expiration = monotonic() + timeout

        @functools.wraps(func)
        def wrapped_func(*args, **kwargs):
            if monotonic() >= func.expiration:
                func.expiration = monotonic() + timeout

                func.cache_clear()

            return func(*args, **kwargs)

        wrapped_func.cache_info = func.cache_info
        wrapped_func.cache_clear = func.cache_clear

        return wrapped_func

    return wrapper_cache
