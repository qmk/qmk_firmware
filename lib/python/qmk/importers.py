from dotty_dict import dotty
from datetime import date
from pathlib import Path
import json

from qmk.git import git_get_username
from qmk.json_schema import validate
from qmk.path import keyboard, keymaps
from qmk.constants import MCU2BOOTLOADER, LEGACY_KEYCODES
from qmk.json_encoders import InfoJSONEncoder, KeymapJSONEncoder
from qmk.json_schema import deep_update, json_load

TEMPLATE = Path('data/templates/keyboard/')


def replace_placeholders(src, dest, tokens):
    """Replaces the given placeholders in each template file.
    """
    content = src.read_text()
    for key, value in tokens.items():
        content = content.replace(f'%{key}%', value)

    dest.write_text(content)


def _gen_dummy_keymap(name, info_data):
    # Pick the first layout macro and just dump in KC_NOs or something?
    (layout_name, layout_data), *_ = info_data["layouts"].items()
    layout_length = len(layout_data["layout"])

    keymap_data = {
        "keyboard": name,
        "layout": layout_name,
        "layers": [["KC_NO" for _ in range(0, layout_length)]],
    }

    return keymap_data


def _extract_kbfirmware_layout(kbf_data):
    layout = []
    for key in kbf_data['keyboard.keys']:
        item = {
            'matrix': [key['row'], key['col']],
            'x': key['state']['x'],
            'y': key['state']['y'],
        }
        if key['state']['w'] != 1:
            item['w'] = key['state']['w']
        if key['state']['h'] != 1:
            item['h'] = key['state']['h']
        layout.append(item)

    return layout


def _extract_kbfirmware_keymap(kbf_data):
    keymap_data = {
        'keyboard': kbf_data['keyboard.settings.name'].lower(),
        'layout': 'LAYOUT',
        'layers': [],
    }

    for i in range(15):
        layer = []
        for key in kbf_data['keyboard.keys']:
            keycode = key['keycodes'][i]['id']
            keycode = LEGACY_KEYCODES.get(keycode, keycode)
            if '()' in keycode:
                fields = key['keycodes'][i]['fields']
                keycode = f'{keycode.split(")")[0]}{",".join(map(str, fields))})'
            layer.append(keycode)
        if set(layer) == {'KC_TRNS'}:
            break
        keymap_data['layers'].append(layer)

    return keymap_data


def import_keymap(keymap_data):
    # Validate to ensure we don't have to deal with bad data - handles stdin/file
    validate(keymap_data, 'qmk.keymap.v1')

    kb_name = keymap_data['keyboard']
    km_name = keymap_data['keymap']

    km_folder = keymaps(kb_name)[0] / km_name
    keyboard_keymap = km_folder / 'keymap.json'

    # This is the deepest folder in the expected tree
    keyboard_keymap.parent.mkdir(parents=True, exist_ok=True)

    # Dump out all those lovely files
    keyboard_keymap.write_text(json.dumps(keymap_data, cls=KeymapJSONEncoder, sort_keys=True))

    return (kb_name, km_name)


def import_keyboard(info_data, keymap_data=None):
    # Validate to ensure we don't have to deal with bad data - handles stdin/file
    validate(info_data, 'qmk.api.keyboard.v1')

    # And validate some more as everything is optional
    if not all(key in info_data for key in ['keyboard_name', 'layouts']):
        raise ValueError('invalid json config')

    kb_name = info_data['keyboard_name']

    # bail
    kb_folder = keyboard(kb_name)
    if kb_folder.exists():
        raise ValueError(f'Keyboard {{fg_cyan}}{kb_name}{{fg_reset}} already exists! Please choose a different name.')

    if not keymap_data:
        # TODO: if supports community then grab that instead
        keymap_data = _gen_dummy_keymap(kb_name, info_data)

    keyboard_json = kb_folder / 'keyboard.json'
    keyboard_keymap = kb_folder / 'keymaps' / 'default' / 'keymap.json'

    # begin with making the deepest folder in the tree
    keyboard_keymap.parent.mkdir(parents=True, exist_ok=True)

    user_name = git_get_username()
    if not user_name:
        user_name = 'TODO'

    tokens = {  # Comment here is to force multiline formatting
        'YEAR': str(date.today().year),
        'KEYBOARD': kb_name,
        'USER_NAME': user_name,
        'REAL_NAME': user_name,
    }

    # Dump out all those lovely files
    for file in list(TEMPLATE.iterdir()):
        replace_placeholders(file, kb_folder / file.name, tokens)

    temp = json_load(keyboard_json)
    deep_update(temp, info_data)

    keyboard_json.write_text(json.dumps(temp, cls=InfoJSONEncoder, sort_keys=True))
    keyboard_keymap.write_text(json.dumps(keymap_data, cls=KeymapJSONEncoder, sort_keys=True))

    return kb_name


def import_kbfirmware(kbfirmware_data):
    kbf_data = dotty(kbfirmware_data)

    diode_direction = ["COL2ROW", "ROW2COL"][kbf_data['keyboard.settings.diodeDirection']]
    mcu = ["atmega32u2", "atmega32u4", "at90usb1286"][kbf_data['keyboard.controller']]
    bootloader = MCU2BOOTLOADER.get(mcu, "custom")

    layout = _extract_kbfirmware_layout(kbf_data)
    keymap_data = _extract_kbfirmware_keymap(kbf_data)

    # convert to d/d info.json
    info_data = dotty({
        "keyboard_name": kbf_data['keyboard.settings.name'].lower(),
        "processor": mcu,
        "bootloader": bootloader,
        "diode_direction": diode_direction,
        "matrix_pins": {
            "cols": kbf_data['keyboard.pins.col'],
            "rows": kbf_data['keyboard.pins.row'],
        },
        "layouts": {
            "LAYOUT": {
                "layout": layout,
            }
        }
    })

    if kbf_data['keyboard.pins.num'] or kbf_data['keyboard.pins.caps'] or kbf_data['keyboard.pins.scroll']:
        if kbf_data['keyboard.pins.num']:
            info_data['indicators.num_lock'] = kbf_data['keyboard.pins.num']
        if kbf_data['keyboard.pins.caps']:
            info_data['indicators.caps_lock'] = kbf_data['keyboard.pins.caps']
        if kbf_data['keyboard.pins.scroll']:
            info_data['indicators.scroll_lock'] = kbf_data['keyboard.pins.scroll']

    if kbf_data['keyboard.pins.rgb']:
        info_data['rgblight.animations'] = {  # Comment here is to force multiline formatting
            "breathing": True,
            "rainbow_mood": True,
            "rainbow_swirl": True,
            "snake": True,
            "knight": True,
            "static_gradient": True,
            "twinkle": True
        }
        info_data['rgblight.led_count'] = kbf_data['keyboard.settings.rgbNum']
        info_data['ws2812.pin'] = kbf_data['keyboard.pins.rgb']

    if kbf_data['keyboard.pins.led']:
        info_data['backlight.levels'] = kbf_data['keyboard.settings.backlightLevels']
        info_data['backlight.pin'] = kbf_data['keyboard.pins.led']

    # delegate as if it were a regular keyboard import
    return import_keyboard(info_data.to_dict(), keymap_data)
