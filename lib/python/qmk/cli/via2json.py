"""Generate a keymap.c from a configurator export.
"""
import json
import re

from milc import cli

import qmk.keyboard
import qmk.path
from qmk.info import info_json
from qmk.json_encoders import KeymapJSONEncoder
from qmk.commands import parse_configurator_json, dump_lines
from qmk.keymap import generate_json, list_keymaps, locate_keymap, parse_keymap_c


def _find_via_layout_macro(keyboard):
    keymap_layout = None
    if 'via' in list_keymaps(keyboard):
        keymap_path = locate_keymap(keyboard, 'via')
        if keymap_path.suffix == '.json':
            keymap_layout = parse_configurator_json(keymap_path)['layout']
        else:
            keymap_layout = parse_keymap_c(keymap_path)['layers'][0]['layout']
    return keymap_layout


def _convert_macros(via_macros):
    via_macros = list(filter(lambda f: bool(f), via_macros))
    if len(via_macros) == 0:
        return list()
    split_regex = re.compile(r'(}\,)|(\,{)')
    macros = list()
    for via_macro in via_macros:
        # Split VIA macro to its elements
        macro = split_regex.split(via_macro)
        # Remove junk elements (None, '},' and ',{')
        macro = list(filter(lambda f: False if f in (None, '},', ',{') else True, macro))
        macro_data = list()
        for m in macro:
            if '{' in m or '}' in m:
                # Found keycode(s)
                keycodes = m.split(',')
                # Remove whitespaces and curly braces from around keycodes
                keycodes = list(map(lambda s: s.strip(' {}'), keycodes))
                # Remove the KC prefix
                keycodes = list(map(lambda s: s.replace('KC_', ''), keycodes))
                macro_data.append({"action": "tap", "keycodes": keycodes})
            else:
                # Found text
                macro_data.append(m)
        macros.append(macro_data)

    return macros


def _fix_macro_keys(keymap_data):
    macro_no = re.compile(r'MACRO0?([0-9]{1,2})')
    for i in range(0, len(keymap_data)):
        for j in range(0, len(keymap_data[i])):
            kc = keymap_data[i][j]
            m = macro_no.match(kc)
            if m:
                keymap_data[i][j] = f'MACRO_{m.group(1)}'
    return keymap_data


def _via_to_keymap(via_backup, keyboard_data, keymap_layout):
    # Check if passed LAYOUT is correct
    layout_data = keyboard_data['layouts'].get(keymap_layout)
    if not layout_data:
        cli.log.error(f'LAYOUT macro {keymap_layout} is not a valid one for keyboard {cli.args.keyboard}!')
        exit(1)

    layout_data = layout_data['layout']
    sorting_hat = list()
    for index, data in enumerate(layout_data):
        sorting_hat.append([index, data['matrix']])

    sorting_hat.sort(key=lambda k: (k[1][0], k[1][1]))

    pos = 0
    for row_num in range(0, keyboard_data['matrix_size']['rows']):
        for col_num in range(0, keyboard_data['matrix_size']['cols']):
            if pos >= len(sorting_hat) or sorting_hat[pos][1][0] != row_num or sorting_hat[pos][1][1] != col_num:
                sorting_hat.insert(pos, [None, [row_num, col_num]])
            else:
                sorting_hat.append([None, [row_num, col_num]])
            pos += 1

    keymap_data = list()
    for layer in via_backup['layers']:
        pos = 0
        layer_data = list()
        for key in layer:
            if sorting_hat[pos][0] is not None:
                layer_data.append([sorting_hat[pos][0], key])
            pos += 1
        layer_data.sort()
        layer_data = [kc[1] for kc in layer_data]
        keymap_data.append(layer_data)

    return keymap_data


@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', type=qmk.path.FileType('r'), arg_only=True, help='VIA Backup JSON file')
@cli.argument('-kb', '--keyboard', type=qmk.keyboard.keyboard_folder, completer=qmk.keyboard.keyboard_completer, arg_only=True, required=True, help='The keyboard\'s name')
@cli.argument('-km', '--keymap', arg_only=True, default='via2json', help='The keymap\'s name')
@cli.argument('-l', '--layout', arg_only=True, help='The keymap\'s layout')
@cli.subcommand('Convert a VIA backup json to keymap.json format.')
def via2json(cli):
    """Convert a VIA backup json to keymap.json format.

    This command uses the `qmk.keymap` module to generate a keymap.json from a VIA backup json. The generated keymap is written to stdout, or to a file if -o is provided.
    """
    # Find appropriate layout macro
    keymap_layout = cli.args.layout if cli.args.layout else _find_via_layout_macro(cli.args.keyboard)
    if not keymap_layout:
        cli.log.error(f"Couldn't find LAYOUT macro for keyboard {cli.args.keyboard}. Please specify it with the '-l' argument.")
        exit(1)

    # Load the VIA backup json
    with cli.args.filename.open('r') as fd:
        via_backup = json.load(fd)

    # Generate keyboard metadata
    keyboard_data = info_json(cli.args.keyboard)

    # Get keycode array
    keymap_data = _via_to_keymap(via_backup, keyboard_data, keymap_layout)

    # Convert macros
    macro_data = list()
    if via_backup.get('macros'):
        macro_data = _convert_macros(via_backup['macros'])

        # Replace VIA macro keys with JSON keymap ones
        keymap_data = _fix_macro_keys(keymap_data)

    # Generate the keymap.json
    keymap_json = generate_json(cli.args.keymap, cli.args.keyboard, keymap_layout, keymap_data, macro_data)

    keymap_lines = [json.dumps(keymap_json, cls=KeymapJSONEncoder, sort_keys=True)]
    dump_lines(cli.args.output, keymap_lines, cli.args.quiet)
