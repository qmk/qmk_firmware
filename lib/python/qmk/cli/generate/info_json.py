"""Keyboard information script.

Compile an info.json for a particular keyboard and pretty-print it.
"""
import json

from milc import cli

from qmk.info_json_encoder import InfoJSONEncoder
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.info import info_json
from qmk.path import is_keyboard


@cli.argument('-kb', '--keyboard', help='Keyboard to show info for.')
@cli.argument('-km', '--keymap', help='Show the layers for a JSON keymap too.')
@cli.subcommand('Generate an info.json file for a keyboard.', hidden=False if cli.config.user.developer else True)
@automagic_keyboard
@automagic_keymap
def generate_info_json(cli):
    """Generate an info.json file for a keyboard
    """
    # Determine our keyboard(s)
    if not cli.config.generate_info_json.keyboard:
        cli.log.error('Missing paramater: --keyboard')
        cli.subcommands['info'].print_help()
        return False

    if not is_keyboard(cli.config.generate_info_json.keyboard):
        cli.log.error('Invalid keyboard: "%s"', cli.config.generate_info_json.keyboard)
        return False

    # Build the info.json file
    kb_info_json = info_json(cli.config.generate_info_json.keyboard)
    pared_down_json = {}

    for key in ('manufacturer', 'maintainer', 'usb', 'keyboard_name', 'width', 'height', 'diode_direction', 'matrix_pins', 'url'):
        if key in kb_info_json:
            pared_down_json[key] = kb_info_json[key]

    pared_down_json['layouts'] = {}
    if 'layouts' in pared_down_json:
        for layout_name, layout in kb_info_json['layouts'].items():
            pared_down_json['layouts'][layout_name] = {}
            pared_down_json['layouts'][layout_name]['key_count'] = layout.get('key_count', len(layout['layout']))
            pared_down_json['layouts'][layout_name]['layout'] = layout['layout']

    # Display the results
    print(json.dumps(pared_down_json, indent=2, cls=InfoJSONEncoder))
