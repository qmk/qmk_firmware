"""Functions that build make commands
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
    if target is None:
        return ['make', ':'.join((keyboard, keymap))]
    return ['make', ':'.join((keyboard, keymap, target))]


def parse_configurator_json(configurator_filename):
    """Open and parse a configurator json export
    """
    file = open(configurator_filename)
    user_keymap = json.load(file)
    file.close()
    return user_keymap


def compile_configurator_json(configurator_filename, bootloader=None):
    """Convert a configurator export JSON file into a C file

    Args:
        configurator_filename
            The configurator JSON export file

        bootloader
            A bootloader to flash

    Returns:
        A command to run to compile and flash the C file.
    """
    # Parse the configurator json
    user_keymap = parse_configurator_json(configurator_filename)

    # Write the keymap C file
    qmk.keymap.write(user_keymap['keyboard'], user_keymap['keymap'], user_keymap['layout'], user_keymap['layers'])

    # Return a command that can be run to make the keymap and flash if given
    if bootloader is None:
        return create_make_command(user_keymap['keyboard'], user_keymap['keymap'])
    return create_make_command(user_keymap['keyboard'], user_keymap['keymap'], bootloader)
