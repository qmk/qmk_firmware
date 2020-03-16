"""Helper functions for commands.
"""
import json

import qmk.keymap


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


def compile_configurator_json(user_keymap, bootloader=None, experimental=False):
    """Convert a configurator export JSON file into a C file

    Args:

        configurator_filename
            The configurator JSON export file

        bootloader
            A bootloader to flash

        experimental
            True if the user wants to attempt compilation with encoder support.

    Returns:

        A command to run to compile and flash the C file.
    """
    # Find the encoders, if any
    encoders = None if 'encoders' not in user_keymap.keys() else user_keymap['encoders']

    # Write the keymap C file
    qmk.keymap.write(user_keymap['keyboard'], user_keymap['keymap'], user_keymap['layout'], user_keymap['layers'], encoders, experimental)

    # Return a command that can be run to make the keymap and flash if given
    if bootloader is None:
        return create_make_command(user_keymap['keyboard'], user_keymap['keymap'])
    return create_make_command(user_keymap['keyboard'], user_keymap['keymap'], bootloader)


def parse_configurator_json(configurator_file):
    """Open and parse a configurator json export
    """
    user_keymap = json.load(configurator_file)

    return user_keymap
