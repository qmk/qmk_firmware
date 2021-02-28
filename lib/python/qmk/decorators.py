"""Helpful decorators that subcommands can use.
"""
import functools
from pathlib import Path
from time import monotonic

from milc import cli

from qmk.keymap import is_keymap_dir
from qmk.path import is_keyboard, under_qmk_firmware


def automagic_keyboard(func):
    """Sets `cli.config.<subcommand>.keyboard` based on environment.

    This will rewrite cli.config.<subcommand>.keyboard if the user did not pass `--keyboard` and the directory they are currently in is a keyboard or keymap directory.
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # Check to make sure their copy of MILC supports config_source
        if not hasattr(cli, 'config_source'):
            cli.log.error("This subcommand requires a newer version of the QMK CLI. Please upgrade using `pip3 install --upgrade qmk` or your package manager.")
            exit(1)

        # Ensure that `--keyboard` was not passed and CWD is under `qmk_firmware/keyboards`
        if cli.config_source[cli._entrypoint.__name__]['keyboard'] != 'argument':
            relative_cwd = under_qmk_firmware()

            if relative_cwd and len(relative_cwd.parts) > 1 and relative_cwd.parts[0] == 'keyboards':
                # Attempt to extract the keyboard name from the current directory
                current_path = Path('/'.join(relative_cwd.parts[1:]))

                if 'keymaps' in current_path.parts:
                    # Strip current_path of anything after `keymaps`
                    keymap_index = len(current_path.parts) - current_path.parts.index('keymaps') - 1
                    current_path = current_path.parents[keymap_index]

                if is_keyboard(current_path):
                    cli.config[cli._entrypoint.__name__]['keyboard'] = str(current_path)
                    cli.config_source[cli._entrypoint.__name__]['keyboard'] = 'keyboard_directory'

        return func(*args, **kwargs)

    return wrapper


def automagic_keymap(func):
    """Sets `cli.config.<subcommand>.keymap` based on environment.

    This will rewrite cli.config.<subcommand>.keymap if the user did not pass `--keymap` and the directory they are currently in is a keymap, layout, or user directory.
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # Check to make sure their copy of MILC supports config_source
        if not hasattr(cli, 'config_source'):
            cli.log.error("This subcommand requires a newer version of the QMK CLI. Please upgrade using `pip3 install --upgrade qmk` or your package manager.")
            exit(1)

        # Ensure that `--keymap` was not passed and that we're under `qmk_firmware`
        if cli.config_source[cli._entrypoint.__name__]['keymap'] != 'argument':
            relative_cwd = under_qmk_firmware()

            if relative_cwd and len(relative_cwd.parts) > 1:
                # If we're in `qmk_firmware/keyboards` and `keymaps` is in our path, try to find the keyboard name.
                if relative_cwd.parts[0] == 'keyboards' and 'keymaps' in relative_cwd.parts:
                    current_path = Path('/'.join(relative_cwd.parts[1:]))  # Strip 'keyboards' from the front

                    if 'keymaps' in current_path.parts and current_path.name != 'keymaps':
                        while current_path.parent.name != 'keymaps':
                            current_path = current_path.parent
                        cli.config[cli._entrypoint.__name__]['keymap'] = current_path.name
                        cli.config_source[cli._entrypoint.__name__]['keymap'] = 'keymap_directory'

                # If we're in `qmk_firmware/layouts` guess the name from the community keymap they're in
                elif relative_cwd.parts[0] == 'layouts' and is_keymap_dir(relative_cwd):
                    cli.config[cli._entrypoint.__name__]['keymap'] = relative_cwd.name
                    cli.config_source[cli._entrypoint.__name__]['keymap'] = 'layouts_directory'

                # If we're in `qmk_firmware/users` guess the name from the userspace they're in
                elif relative_cwd.parts[0] == 'users':
                    # Guess the keymap name based on which userspace they're in
                    cli.config[cli._entrypoint.__name__]['keymap'] = relative_cwd.parts[1]
                    cli.config_source[cli._entrypoint.__name__]['keymap'] = 'users_directory'

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
