from dotty_dict import dotty
import json

from qmk.json_schema import validate
from qmk.path import keyboard, keymap
from qmk.constants import MCU2BOOTLOADER
from qmk.json_encoders import InfoJSONEncoder, KeymapJSONEncoder


def _gen_dummy_keymap(name, info_data):
    # Pick the first layout macro and just dump in KC_NOs or something?
    (layout_name, layout_data), *_ = info_data["layouts"].items()
    layout_length = len(layout_data["layout"])

    keymap_data = {
        "keyboard": name,
        "layout": layout_name,
        "layers": [["KC_NO" for _ in range(0, layout_length)]],
    }

    return json.dumps(keymap_data, cls=KeymapJSONEncoder)


def import_keymap(keymap_data):
    # Validate to ensure we don't have to deal with bad data - handles stdin/file
    validate(keymap_data, 'qmk.keymap.v1')

    kb_name = keymap_data['keyboard']
    km_name = keymap_data['keymap']

    km_folder = keymap(kb_name) / km_name
    keyboard_keymap = km_folder / 'keymap.json'

    # This is the deepest folder in the expected tree
    keyboard_keymap.parent.mkdir(parents=True, exist_ok=True)

    # Dump out all those lovely files
    keyboard_keymap.write_text(json.dumps(keymap_data, cls=KeymapJSONEncoder))

    return (kb_name, km_name)


def import_keyboard(info_data):
    # Validate to ensure we don't have to deal with bad data - handles stdin/file
    validate(info_data, 'qmk.api.keyboard.v1')

    # And validate some more as everything is optional
    if not all(key in info_data for key in ['keyboard_name', 'layouts']):
        raise ValueError('invalid info.json')

    kb_name = info_data['keyboard_name']

    # bail
    kb_folder = keyboard(kb_name)
    if kb_folder.exists():
        raise ValueError(f'Keyboard {{fg_cyan}}{kb_name}{{fg_reset}} already exists! Please choose a different name.')

    keyboard_info = kb_folder / 'info.json'
    keyboard_rules = kb_folder / 'rules.mk'
    keyboard_keymap = kb_folder / 'keymaps' / 'default' / 'keymap.json'

    # This is the deepest folder in the expected tree
    keyboard_keymap.parent.mkdir(parents=True, exist_ok=True)

    # Dump out all those lovely files
    keyboard_info.write_text(json.dumps(info_data, cls=InfoJSONEncoder))
    keyboard_rules.write_text("# This file intentionally left blank")
    keyboard_keymap.write_text(_gen_dummy_keymap(kb_name, info_data))

    return kb_name


def import_kbfirmware(kbfirmware_data):
    kbf_data = dotty(kbfirmware_data)

    diode_direction = ["COL2ROW", "ROW2COL"][kbf_data['keyboard.settings.diodeDirection']]
    mcu = ["atmega32u2", "atmega32u4", "at90usb1286"][kbf_data['keyboard.controller']]
    bootloader = MCU2BOOTLOADER.get(mcu, "custom")

    layout = []
    for key in kbf_data['keyboard.keys']:
        layout.append({
            "matrix": [key["row"], key["col"]],
            "x": key["state"]["x"],
            "y": key["state"]["y"],
            "w": key["state"]["w"],
            "h": key["state"]["h"],
        })

    # convert to d/d info.json
    info_data = {
        "keyboard_name": kbf_data['keyboard.settings.name'].lower(),
        "manufacturer": "TODO",
        "maintainer": "TODO",
        "processor": mcu,
        "bootloader": bootloader,
        "diode_direction": diode_direction,
        "matrix_pins": {
            "cols": kbf_data['keyboard.pins.col'],
            "rows": kbf_data['keyboard.pins.row'],
        },
        "usb": {
            "vid": "0xFEED",
            "pid": "0x0000",
            "device_version": "0.0.1",
        },
        "features": {
            "bootmagic": True,
            "command": False,
            "console": False,
            "extrakey": True,
            "mousekey": True,
            "nkro": True,
        },
        "layouts": {
            "LAYOUT": {
                "layout": layout,
            }
        }
    }

    if kbf_data['keyboard.pins.num'] or kbf_data['keyboard.pins.caps'] or kbf_data['keyboard.pins.scroll']:
        indicators = {}
        if kbf_data['keyboard.pins.num']:
            indicators['num_lock'] = kbf_data['keyboard.pins.num']
        if kbf_data['keyboard.pins.caps']:
            indicators['caps_lock'] = kbf_data['keyboard.pins.caps']
        if kbf_data['keyboard.pins.scroll']:
            indicators['scroll_lock'] = kbf_data['keyboard.pins.scroll']
        info_data['indicators'] = indicators

    if kbf_data['keyboard.pins.rgb']:
        info_data['rgblight'] = {
            'animations': {
                'all': True
            },
            'led_count': kbf_data['keyboard.settings.rgbNum'],
            'pin': kbf_data['keyboard.pins.rgb'],
        }

    if kbf_data['keyboard.pins.led']:
        info_data['backlight'] = {
            'levels': kbf_data['keyboard.settings.backlightLevels'],
            'pin': kbf_data['keyboard.pins.led'],
        }

    # delegate as if it were a regular keyboard import
    return import_keyboard(info_data)
