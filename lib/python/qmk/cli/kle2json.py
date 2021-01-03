"""Convert raw KLE to JSON
"""
import json
import os
from pathlib import Path

from milc import cli
from kle2xy import KLE2xy

import qmk.path
from qmk.converter import kle2qmk
from qmk.decorators import automagic_keyboard
from qmk.info import info_json
from qmk.info_json_encoder import InfoJSONEncoder


@cli.argument('kle', arg_only=True, help='A file or KLE id to convert')
@cli.argument('--vid', arg_only=True, default='0x03A8', help='USB VID (Default: 0x03A8)')
@cli.argument('--pid', arg_only=True, default='0x0000', help='USB PID (Default: 0x0000)')
@cli.argument('-m', '--manufacturer', arg_only=True, default='', help='Manufacturer of the keyboard')
@cli.argument('-l', '--layout', arg_only=True, default='LAYOUT', help='The LAYOUT name this KLE represents')
@cli.argument('-kb', '--keyboard', arg_only=True, required=True, help='The folder name for the keyboard')
@cli.argument('-km', '--keymap', arg_only=True, default='default', help='The name of the keymap to write (Default: default)')
@cli.argument('-d', '--diode', arg_only=True, default='COL2ROW', help='The diode direction for the keyboard (COL2ROW, ROW2COL)')
@cli.subcommand('Use a KLE layout to build info.json and a keymap', hidden=False if cli.config.user.developer else True)
def kle2json(cli):
    """Convert a KLE layout to QMK's layout format.
    """
    file_path = Path(os.environ['ORIG_CWD'], cli.args.kle)

    # Find our KLE text
    if file_path.exists():
        raw_code = file_path.open().read()

    else:
        if cli.args.kle.startswith('http') and '#' in cli.args.kle:
            kle_path = cli.args.kle.split('#', 1)[1]
            if 'gists' not in kle_path:
                cli.log.error('Invalid KLE url: {fg_cyan}%s', cli.args.kle)
                return False
            else:
                print('FIXME: fetch gist')
                return False
        else:
            cli.log.error('File {fg_cyan}%s{style_reset_all} was not found.', file_path)
            return False

    # Make sure the user supplied a keyboard
    if not cli.args.keyboard:
        cli.log.error('You must pass --keyboard or be in a keyboard directory!')
        cli.print_usage()
        return False

    # Check for an existing info.json
    if qmk.path.is_keyboard(cli.args.keyboard):
        kb_info_json = info_json(cli.args.keyboard)
    else:
        kb_info_json = {
            "manufacturer": cli.args.manufacturer,
            "keyboard_name": cli.args.keyboard,
            "maintainer": "",
            "diode_direction": cli.args.diode,
            "features": {
                "console": True,
                "extrakey": True,
                "mousekey": True,
                "nkro": True
            },
            "matrix_pins": {
                "cols": [],
                "rows": [],
            },
            "usb": {
              "device_ver": "0x0001",
              "pid": cli.args.pid,
              "vid": cli.args.vid
            },
            "layouts": {},
        }

    # Build and merge in the new layout
    try:
        # Convert KLE raw to x/y coordinates (using kle2xy package from skullydazed)
        kle = KLE2xy(raw_code)
    except Exception as e:
        cli.log.error('Could not parse KLE raw data: %s', raw_code)
        cli.log.exception(e)
        return False

    if 'layouts' not in kb_info_json:
        kb_info_json['layouts'] = {}

    if cli.args.layout not in kb_info_json['layouts']:
        kb_info_json['layouts'][cli.args.layout] = {}

    kb_info_json['layouts'][cli.args.layout]['layout'] = kle2qmk(kle)

    # Write our info.json
    keyboard_dir = qmk.path.keyboard(cli.args.keyboard)
    keyboard_dir.mkdir(exist_ok=True, parents=True)
    info_json_file = keyboard_dir / 'info.json'

    json.dump(kb_info_json, info_json_file.open('w'), indent=4, separators=(', ', ': '), sort_keys=False, cls=InfoJSONEncoder)
    cli.log.info('Wrote file {fg_cyan}%s', info_json_file)

    # Generate and write a keymap
    keymap_path = keyboard_dir / 'keymaps' / cli.args.keymap
    keymap_file = keymap_path / 'keymap.json'

    if keymap_path.exists():
        cli.log.warning('{fg_cyan}%s{fg_reset} already exists, not generating a keymap.', keymap_path)
    else:
        keymap = [key.get('label', 'KC_NO') for key in kb_info_json['layouts'][cli.args.layout]['layout']]
        keymap_json = {
                'version': 1,
                'documentation': "This file is a QMK Keymap. You can compile it with `qmk compile` or import it at <https://config.qmk.fm>. It can also be used directly with QMK's source code.",
                'author': '',
                'keyboard': kb_info_json['keyboard_name'],
                'keymap': cli.args.keymap,
                'layout': cli.args.layout,
                'layers': [
                    keymap,
                    ['KC_TRNS' for key in keymap],
                ],
        }
        keymap_path.mkdir(exist_ok=True, parents=True)

        json.dump(keymap_json, keymap_file.open('w'), indent=4, separators=(', ', ': '), sort_keys=False)
        cli.log.info('Wrote file %s', keymap_file)
