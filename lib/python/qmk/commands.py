"""Functions that build make commands
"""
import json
import qmk.keymap


def create_make_command(keyboard, keymap, special=None, target=None):
    """Create a make compile command

    Args:
        keyboard
            The path of the keyboard, for example 'plank'

        keymap
            The name of the keymap, for example 'algernon'

        special
            optional features to enable

        target
            Usually a bootloader.

    Returns:
        A command that can be run to make the specified keyboard and keymap
    """

    command = ['make']
    if special is not None and len(special) > 0:
        options = ''
        for value, key in enumerate(special):
            options += '%s=%s ' (key, special[key])
        command.append(options)

    if target is None:
        command.append(':'.join((keyboard, keymap)))
    else:
        command.append(':'.join((keyboard, keymap, target)))

    return command


def parse_configurator_json(configurator_file):
    """Open and parse a configurator json export
    """
    user_keymap = json.load(configurator_file)
    return user_keymap


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

    # scan keymap for special codes
    special = {'MOUSE_ENABLE': 'no'}
    for layer_num, layer in enumerate(user_keymap['layers']):
        # check each key for special keys of interest
        for key_pos, key in enumerate(layer):
            ret = special_keys(key)
            if (ret != 'IGNORE'):
                special[ret] = 'yes'

    # Write the keymap C file
    qmk.keymap.write(user_keymap['keyboard'], user_keymap['keymap'], user_keymap['layout'], user_keymap['layers'])

    # Return a command that can be run to make the keymap and flash if given
    if bootloader is None:
        return create_make_command(user_keymap['keyboard'], user_keymap['keymap'], special)
    return create_make_command(user_keymap['keyboard'], user_keymap['keymap'], special, bootloader)


# used to turn out features based on presence of codes in keymap
def special_keys(kc):
    switcher = {
        'KC_MS_U': 'MOUSE_ENABLE',
        'KC_MS_D': 'MOUSE_ENABLE',
        'KC_MS_L': 'MOUSE_ENABLE',
        'KC_MS_R': 'MOUSE_ENABLE',
        'KC_BTN1': 'MOUSE_ENABLE',
        'KC_BTN2': 'MOUSE_ENABLE',
        'KC_BTN3': 'MOUSE_ENABLE',
        'KC_BTN4': 'MOUSE_ENABLE',
        'KC_BTN5': 'MOUSE_ENABLE',
        'KC_WH_U': 'MOUSE_ENABLE',
        'KC_WH_D': 'MOUSE_ENABLE',
        'KC_WH_L': 'MOUSE_ENABLE',
        'KC_WH_R': 'MOUSE_ENABLE',
        'KC_ACL0': 'MOUSE_ENABLE',
        'KC_ALC1': 'MOUSE_ENABLE',
        'KC_ACL2': 'MOUSE_ENABLE'
    }
    return switcher.get(kc, "IGNORE")
