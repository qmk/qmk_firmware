"""Helper functions for commands.
"""
import json
from pathlib import Path

from milc import cli

import qmk.keymap
from qmk.path import is_keyboard, is_keymap_dir, under_qmk_firmware


def create_make_command(keyboard, keymap, target=None):
    """Create a make compile command

    Args:

        keyboard
            The path of the keyboard, for example 'plank'

        keymap
            The name of the keymap, for example 'algernon'

        target
            Usually a bootloader.

    Returns:

        A command that can be run to make the specified keyboard and keymap
    """
    make_args = [keyboard, keymap]

    if target:
        make_args.append(target)

    return ['make', ':'.join(make_args)]


def compile_configurator_json(user_keymap, bootloader=None):
    """Convert a configurator export JSON file into a C file

    Args:

        configurator_filename
            The configurator JSON export file

        bootloader
            A bootloader to flash

    Returns:

        A command to run to compile and flash the C file.
    """
    # Write the keymap C file
    qmk.keymap.write(user_keymap['keyboard'], user_keymap['keymap'], user_keymap['layout'], user_keymap['layers'])

    # Return a command that can be run to make the keymap and flash if given
    if bootloader is None:
        return create_make_command(user_keymap['keyboard'], user_keymap['keymap'])
    return create_make_command(user_keymap['keyboard'], user_keymap['keymap'], bootloader)


def find_keyboard_keymap():
    """Returns `(keyboard_name, keymap_name)` based on the user's current environment.

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
        if relative_cwd and relative_cwd.parts and relative_cwd.parts[0] == 'keyboards':
            # Try to determine the keyboard and/or keymap name
            current_path = Path('/'.join(relative_cwd.parts[1:]))

            if current_path.parts[-2] == 'keymaps':
                if not keymap_name:
                    keymap_name = current_path.parts[-1]
                if not keyboard_name:
                    keyboard_name = '/'.join(current_path.parts[:-2])
            elif not keyboard_name and is_keyboard(current_path):
                keyboard_name = str(current_path)

        elif relative_cwd and relative_cwd.parts and relative_cwd.parts[0] == 'layouts':
            # Try to determine the keymap name from the community layout
            if is_keymap_dir(relative_cwd) and not keymap_name:
                keymap_name = relative_cwd.name

        elif relative_cwd and relative_cwd.parts and relative_cwd.parts[0] == 'users':
            # Try to determine the keymap name based on which userspace they're in
            if not keymap_name and len(relative_cwd.parts) > 1:
                keymap_name = relative_cwd.parts[1]

    # If we still don't have a keyboard and keymap check the config
    if not keyboard_name and cli.config[cli._entrypoint.__name__]['keyboard']:
        keyboard_name = cli.config[cli._entrypoint.__name__]['keyboard']

    if not keymap_name and cli.config[cli._entrypoint.__name__]['keymap']:
        keymap_name = cli.config[cli._entrypoint.__name__]['keymap']

    return (keyboard_name, keymap_name)


def parse_configurator_json(configurator_file):
    """Open and parse a configurator json export
    """
    user_keymap = json.load(configurator_file)

    return user_keymap
