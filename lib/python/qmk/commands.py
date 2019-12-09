"""Functions that build make commands
"""
import json
import qmk.keymap


def create_make_command(keyboard, keymap, target=None, special=None):
    """Create a make compile command

    Args:
        keyboard
            The path of the keyboard, for example 'plank'

        keymap
            The name of the keymap, for example 'algernon'

        target
            Usually a bootloader.

        special
            optional features to enable

    Returns:
        A command that can be run to make the specified keyboard and keymap
    """

    command = ['make']

    # Add specified rules to command line invocation to
    # enable optional keymap features.
    if special and len(special) > 0:
        for value, key in enumerate(special):
            option = '%s=%s' % (key, special[key])
            command.append(option)

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
    special = scan_keymap(user_keymap['layers'])

    # Write the keymap C file
    qmk.keymap.write(user_keymap['keyboard'], user_keymap['keymap'], user_keymap['layout'], user_keymap['layers'])

    # Return a command that can be run to make the keymap and flash if given
    if bootloader is None:
        return create_make_command(user_keymap['keyboard'], user_keymap['keymap'], None, special)
    return create_make_command(user_keymap['keyboard'], user_keymap['keymap'], bootloader, special)


def scan_keymap(layers):
    """Scan layer dictionary and detect keycodes of interest

    Args:
        layers
        dictionary of nested arrays containing the keymap

    Returns:
        A dictionary of rules to enable dynamically.
    """

    special = {}
    for layer_num, layer in enumerate(layers):
        # check each key for special keys of interest
        for key_pos, key in enumerate(layer):
            ret = special_keys(key)
            if (ret != 'IGNORE'):
                special[ret] = 'yes'

    return special


# used to turn on features based on presence of codes in keymap
def special_keys(kc):
    """ check keycode and return matching rules or IGNORE

    Args:
        kc
        Keycode as a string

    Returns:
        A matching rule or IGNORE
    """

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
        'KC_ACL2': 'MOUSE_ENABLE',
        'BL_TOGG': 'BACKLIGHT_ENABLE',
        'BL_STEP': 'BACKLIGHT_ENABLE',
        'BL_ON': 'BACKLIGHT_ENABLE',
        'BL_OFF': 'BACKLIGHT_ENABLE',
        'BL_INC': 'BACKLIGHT_ENABLE',
        'BL_DEC': 'BACKLIGHT_ENABLE',
        'BL_BRTG': 'BACKLIGHT_ENABLE',
        'VLK_TOG': 'VELOCIKEY_ENABLE',
        'UC_MOD': 'UCIS_ENABLE',
        'UC_RMOD': 'UCIS_ENABLE',
        'UC_M_OSX': 'UCIS_ENABLE',
        'UC_M_LN': 'UCIS_ENABLE',
        'UC_M_WI': 'UCIS_ENABLE',
        'UC_M_BS': 'UCIS_ENABLE',
        'UC_M_WC': 'UCIS_ENABLE',
        'UC_M_WC': 'UCIS_ENABLE',
    }
    return switcher.get(kc, "IGNORE")
