from dotty_dict import dotty
import json

from milc import cli

from qmk.json_schema import json_load, validate
from qmk.path import keyboard, keymap, FileType
from qmk.constants import MCU2BOOTLOADER


def _gen_dummy_keymap(name, info_data):
    # Pick the first layout macro and just dump in KC_NOs or something?
    (layout_name, layout_data), *_ = info_data["layouts"].items()
    layout_length = len(layout_data["layout"])

    keymap_data = {
        "keyboard": name,
        "layout": layout_name,
        "layers": [["KC_NO" for _ in range(0, layout_length)]],
    }

    return json.dumps(keymap_data)


def _import_keymap(keymap_data):
    # Validate to ensure we don't have to deal with bad data - handles stdin/file
    validate(keymap_data, 'qmk.keymap.v1')

    kb_name = keymap_data['keyboard']
    km_name = keymap_data['keymap']

    km_folder = keymap(kb_name) / km_name
    keyboard_keymap = km_folder / 'keymap.json'

    # This is the deepest folder in the expected tree
    keyboard_keymap.parent.mkdir(parents=True, exist_ok=True)

    # Dump out all those lovely files
    keyboard_keymap.write_text(json.dumps(keymap_data))

    cli.log.info(f'{{fg_green}}Imported a new keymap named {{fg_cyan}}{km_name}{{fg_green}}.{{fg_reset}}')
    cli.log.info(f'To start working on things, `cd` into {{fg_cyan}}keyboards/{kb_name}/keymaps/{km_name}{{fg_reset}},')
    cli.log.info('or open the directory in your preferred text editor.')
    cli.log.info(f"And build with {{fg_yellow}}qmk compile -kb {kb_name} -km {km_name}{{fg_reset}}.")


def _import_keyboard(info_data):
    # Validate to ensure we don't have to deal with bad data - handles stdin/file
    validate(info_data, 'qmk.api.keyboard.v1')

    # And validate some more as everything is optional
    if not all(key in info_data for key in ['keyboard_name', 'layouts']):
        raise ValueError('invalid info.json')

    kb_name = info_data['keyboard_name']

    # bail
    if keyboard(kb_name).exists():
        cli.log.error(f'Keyboard {{fg_cyan}}{kb_name}{{fg_reset}} already exists! Please choose a different name.')
        return 1

    kb_folder = keyboard(kb_name)
    keyboard_info = kb_folder / 'info.json'
    keyboard_rules = kb_folder / 'rules.mk'
    keyboard_keymap = kb_folder / 'keymaps' / 'default' / 'keymap.json'

    # This is the deepest folder in the expected tree
    keyboard_keymap.parent.mkdir(parents=True, exist_ok=True)

    # Dump out all those lovely files
    keyboard_info.write_text(json.dumps(info_data))
    keyboard_rules.write_text("# This file intentionally left blank")
    keyboard_keymap.write_text(_gen_dummy_keymap(kb_name, info_data))

    cli.log.info(f'{{fg_green}}Imported a new keyboard named {{fg_cyan}}{kb_name}{{fg_green}}.{{fg_reset}}')
    cli.log.info(f'To start working on things, `cd` into {{fg_cyan}}keyboards/{kb_name}{{fg_reset}},')
    cli.log.info('or open the directory in your preferred text editor.')
    cli.log.info(f"And build with {{fg_yellow}}qmk compile -kb {kb_name} -km default{{fg_reset}}.")


def _import_kbfirmware(kbfirmware_data):
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
            'animations': {'all': True},
            'led_count': kbf_data['keyboard.settings.rgbNum'],
            'pin': kbf_data['keyboard.pins.rgb'],
        }

    if kbf_data['keyboard.pins.led']:
        info_data['backlight'] = {
            'levels': kbf_data['keyboard.settings.backlightLevels'],
            'pin': kbf_data['keyboard.pins.led'],
        }

    cli.log.warn("Support here is basic - Consider using 'qmk new-keyboard' instead")
    _import_keyboard(info_data)


def cli_subcommand_rename(newname):
    """ Gross workaround to "import" being a keyword and mlic not providing a name override
    """
    def decorator(f):
        f.__name__ = newname
        return f
    return decorator


@cli.argument('filename', type=FileType('r'), nargs='+', arg_only=True, help='file')
@cli.argument('-f', '--format', arg_only=True, help='Format to import (keyboard, keymap, kbfirmware) (Default: ducktype).')
@cli.subcommand('Import some stuffs')
@cli_subcommand_rename('import')
def _import(cli):
    fmt = cli.args.format
    filename = cli.args.filename[0]

    data = json_load(filename)

    # guess at type
    if not cli.args.format:
        if 'keyboard' in data and 'bounds' in data['keyboard']:
            fmt = "kbfirmware"
        elif 'keymap' in data:
            fmt = "keymap"
        else:
            fmt = "keyboard"

    cli.log.info(f'{{style_bright}}Importing {filename.name} as type {fmt}.{{style_normal}}')
    cli.echo('')

    if fmt == "keyboard":
        _import_keyboard(data)
    elif fmt == "keymap":
        _import_keymap(data)
    elif fmt == "kbfirmware":
        _import_kbfirmware(data)
