"""Helpful decorators that subcommands can use.
"""
import functools
from pathlib import Path

from milc import cli

from qmk.path import is_keyboard, is_keymap_dir, under_qmk_firmware


def context_sensitivity(func):
    """Sets `cli.config.<subcommand>.keyboard` and `cli.config.<subcommand>.keymap` based on environment.

    This determines the keyboard and keymap name using the following precedence order:

        * Command line flags (--keyboard and --keymap)
        * Current working directory
            * `keyboards/<keyboard_name>`
            * `keyboards/<keyboard_name>/keymaps/<keymap_name>`
            * `layouts/**/<keymap_name>`
            * `users/<keymap_name>`
        * Configuration
            * cli.config.<subcommand>.keyboard
            * cli.config.<subcommand>.keymap
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # Check to make sure their copy of MILC supports config_source
        if not hasattr(cli, 'config_source'):
            cli.log.error("Your QMK CLI is out of date. Please upgrade using pip3 or your package manager.")
            exit(1)

        # State variables
        relative_cwd = under_qmk_firmware()
        keyboard_name = ""
        keymap_name = ""

        # If the keyboard or keymap are passed as arguments use that in preference to anything else
        if cli.config_source[cli._entrypoint.__name__]['keyboard'] == 'argument':
            keyboard_name = cli.config[cli._entrypoint.__name__]['keyboard']

        if cli.config_source[cli._entrypoint.__name__]['keymap'] == 'argument':
            keymap_name = cli.config[cli._entrypoint.__name__]['keymap']

        if not keyboard_name or not keymap_name:
            # If we don't have a keyboard_name and keymap_name from arguments try to derive one or both
            if relative_cwd and len(relative_cwd.parts) > 1:
                # Try to determine based on being in `qmk_firmware/keyboards`
                if relative_cwd.parts[0] == 'keyboards':
                    current_path = Path('/'.join(relative_cwd.parts[1:]))  # Remove 'keyboards' from the front of the path

                    if current_path.parts[-2] == 'keymaps':
                        if not keymap_name:
                            keymap_name = current_path.parts[-1]
                        if not keyboard_name:
                            keyboard_name = '/'.join(current_path.parts[:-2])
                    elif not keyboard_name and is_keyboard(current_path):
                        keyboard_name = str(current_path)

                # Try to determine based on being in `qmk_firmware/layouts`
                elif relative_cwd.parts[0] == 'layouts':
                    if is_keymap_dir(relative_cwd) and not keymap_name:
                        keymap_name = relative_cwd.name

                # Try to determine based on being in `qmk_firmware/users`
                elif relative_cwd.parts[0] == 'users':
                    if not keymap_name and len(relative_cwd.parts) > 1:
                        keymap_name = relative_cwd.parts[1]

        # If we have a keyboard/keymap name overwrite the config
        if keyboard_name:
            cli.config[cli._entrypoint.__name__]['keyboard'] = keyboard_name

        if keymap_name:
            cli.config[cli._entrypoint.__name__]['keymap'] = keymap_name

        return func(*args, **kwargs)

    return wrapper


def automagic_keyboard(func):
    """Sets `cli.config.<subcommand>.keyboard` based on environment.

    This determines the keyboard name using the following precedence order:

        * Command line flags (--keyboard)
        * Current working directory
            * `keyboards/<keyboard_name>`
        * Configuration
            * cli.config.<subcommand>.keyboard
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # Check to make sure their copy of MILC supports config_source
        if not hasattr(cli, 'config_source'):
            cli.log.error("Your QMK CLI is out of date. Please upgrade using pip3 or your package manager.")
            exit(1)

        # If the keyboard or keymap are passed as arguments use that in preference to anything else
        if cli.config_source[cli._entrypoint.__name__]['keyboard'] == 'argument':
            return func(*args, **kwargs)

        # If the user is in `qmk_firmware/keyboards` try to determine the keyboard name that way
        relative_cwd = under_qmk_firmware()

        if relative_cwd and len(relative_cwd.parts) > 1 and relative_cwd.parts[0] == 'keyboards':
            current_path = Path('/'.join(relative_cwd.parts[1:]))

            if 'keymaps' in current_path.parts:
                # Strip current_path of anything after `keymaps`
                keymap_index = len(current_path.parts) - current_path.parts.index('keymaps') - 1
                current_path = current_path.parents[keymap_index]

            if is_keyboard(current_path):
                cli.config[cli._entrypoint.__name__]['keyboard'] = str(current_path)

        return func(*args, **kwargs)

    return wrapper


def automagic_keymap(func):
    """Sets `cli.config.<subcommand>.keymap` based on environment.

    This determines the keymap name using the following precedence order:

        * Command line flags (--keymap)
        * Current working directory
            * `keyboards/<keyboard_name>/keymaps/<keymap_name>`
            * `layouts/**/<keymap_name>`
            * `users/<keymap_name>`
        * Configuration
            * cli.config.<subcommand>.keymap
    """
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # Check to make sure their copy of MILC supports config_source
        if not hasattr(cli, 'config_source'):
            cli.log.error("Your QMK CLI is out of date. Please upgrade using pip3 or your package manager.")
            exit(1)

        # If the keyboard or keymap are passed as arguments use that in preference to anything else
        if cli.config_source[cli._entrypoint.__name__]['keymap'] == 'argument':
            return func(*args, **kwargs)

        # Check our current directory for a keymap name
        relative_cwd = under_qmk_firmware()

        if relative_cwd and len(relative_cwd.parts) > 1:
            # If we're in `qmk_firmware/keyboards` and `keymaps` is in our path, try to find the keyboard name.
            if relative_cwd.parts[0] == 'keyboards' and 'keymaps' in relative_cwd.parts:
                current_path = Path('/'.join(relative_cwd.parts[1:]))  # Strip 'keyboards' from the front

                if 'keymaps' in current_path.parts and current_path.name != 'keymaps':
                    while current_path.parent.name != 'keymaps':
                        current_path = current_path.parent
                    cli.config[cli._entrypoint.__name__]['keymap'] = current_path.name

            elif relative_cwd.parts[0] == 'layouts' and is_keymap_dir(relative_cwd):
                # Guess the keymap name from the community keymap they're in
                cli.config[cli._entrypoint.__name__]['keymap'] = relative_cwd.name

            elif relative_cwd.parts[0] == 'users':
                # Guess the keymap name based on which userspace they're in
                cli.config[cli._entrypoint.__name__]['keymap'] = relative_cwd.parts[1]

        return func(*args, **kwargs)

    return wrapper
