"""Used by the make system to generate info_config.h from info.json.
"""
from pathlib import Path

from dotty_dict import dotty
from milc import cli

from qmk.info import info_json, keymap_json_config
from qmk.json_schema import json_load
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.commands import dump_lines
from qmk.path import normpath
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE


def direct_pins(direct_pins, postfix):
    """Return the config.h lines that set the direct pins.
    """
    rows = []

    for row in direct_pins:
        cols = ','.join(map(str, [col or 'NO_PIN' for col in row]))
        rows.append('{' + cols + '}')

    return f"""
#ifndef DIRECT_PINS{postfix}
#   define DIRECT_PINS{postfix} {{ {", ".join(rows)} }}
#endif // DIRECT_PINS{postfix}
"""


def pin_array(define, pins, postfix):
    """Return the config.h lines that set a pin array.
    """
    pin_array = ', '.join(map(str, [pin or 'NO_PIN' for pin in pins]))

    return f"""
#ifndef {define}_PINS{postfix}
#   define {define}_PINS{postfix} {{ {pin_array} }}
#endif // {define}_PINS{postfix}
"""


def matrix_pins(matrix_pins, postfix=''):
    """Add the matrix config to the config.h.
    """
    pins = []

    if 'direct' in matrix_pins:
        pins.append(direct_pins(matrix_pins['direct'], postfix))

    if 'cols' in matrix_pins:
        pins.append(pin_array('MATRIX_COL', matrix_pins['cols'], postfix))

    if 'rows' in matrix_pins:
        pins.append(pin_array('MATRIX_ROW', matrix_pins['rows'], postfix))

    return '\n'.join(pins)


def generate_matrix_size(kb_info_json, config_h_lines):
    """Add the matrix size to the config.h.
    """
    if 'matrix_pins' in kb_info_json:
        col_count = kb_info_json['matrix_size']['cols']
        row_count = kb_info_json['matrix_size']['rows']

        config_h_lines.append(f"""
#ifndef MATRIX_COLS
#   define MATRIX_COLS {col_count}
#endif // MATRIX_COLS

#ifndef MATRIX_ROWS
#   define MATRIX_ROWS {row_count}
#endif // MATRIX_ROWS
""")


def generate_config_items(kb_info_json, config_h_lines):
    """Iterate through the info_config map to generate basic config values.
    """
    info_config_map = json_load(Path('data/mappings/info_config.json'))

    for config_key, info_dict in info_config_map.items():
        info_key = info_dict['info_key']
        key_type = info_dict.get('value_type', 'raw')
        to_config = info_dict.get('to_config', True)

        if not to_config:
            continue

        try:
            config_value = kb_info_json[info_key]
        except KeyError:
            continue

        if key_type.startswith('array.array'):
            config_h_lines.append('')
            config_h_lines.append(f'#ifndef {config_key}')
            config_h_lines.append(f'#   define {config_key} {{ {", ".join(["{" + ",".join(list(map(str, x))) + "}" for x in config_value])} }}')
            config_h_lines.append(f'#endif // {config_key}')
        elif key_type.startswith('array'):
            config_h_lines.append('')
            config_h_lines.append(f'#ifndef {config_key}')
            config_h_lines.append(f'#   define {config_key} {{ {", ".join(map(str, config_value))} }}')
            config_h_lines.append(f'#endif // {config_key}')
        elif key_type == 'bool':
            if config_value:
                config_h_lines.append('')
                config_h_lines.append(f'#ifndef {config_key}')
                config_h_lines.append(f'#   define {config_key}')
                config_h_lines.append(f'#endif // {config_key}')
        elif key_type == 'mapping':
            for key, value in config_value.items():
                config_h_lines.append('')
                config_h_lines.append(f'#ifndef {key}')
                config_h_lines.append(f'#   define {key} {value}')
                config_h_lines.append(f'#endif // {key}')
        elif key_type == 'str':
            config_h_lines.append('')
            config_h_lines.append(f'#ifndef {config_key}')
            config_h_lines.append(f'#   define {config_key} "{config_value}"')
            config_h_lines.append(f'#endif // {config_key}')
        elif key_type == 'bcd_version':
            (major, minor, revision) = config_value.split('.')
            config_h_lines.append('')
            config_h_lines.append(f'#ifndef {config_key}')
            config_h_lines.append(f'#   define {config_key} 0x{major.zfill(2)}{minor}{revision}')
            config_h_lines.append(f'#endif // {config_key}')
        else:
            config_h_lines.append('')
            config_h_lines.append(f'#ifndef {config_key}')
            config_h_lines.append(f'#   define {config_key} {config_value}')
            config_h_lines.append(f'#endif // {config_key}')


def generate_encoder_config(encoder_json, config_h_lines, postfix=''):
    """Generate the config.h lines for encoders."""
    a_pads = []
    b_pads = []
    resolutions = []
    for encoder in encoder_json.get("rotary", []):
        a_pads.append(encoder["pin_a"])
        b_pads.append(encoder["pin_b"])
        resolutions.append(str(encoder.get("resolution", 4)))

    config_h_lines.append(f'#ifndef ENCODERS_PAD_A{postfix}')
    config_h_lines.append(f'#   define ENCODERS_PAD_A{postfix} {{ { ", ".join(a_pads) } }}')
    config_h_lines.append(f'#endif // ENCODERS_PAD_A{postfix}')

    config_h_lines.append(f'#ifndef ENCODERS_PAD_B{postfix}')
    config_h_lines.append(f'#   define ENCODERS_PAD_B{postfix} {{ { ", ".join(b_pads) } }}')
    config_h_lines.append(f'#endif // ENCODERS_PAD_B{postfix}')

    if len(set(resolutions)) == 1:
        config_h_lines.append(f'#ifndef ENCODER_RESOLUTION{postfix}')
        config_h_lines.append(f'#   define ENCODER_RESOLUTION{postfix} { resolutions[0] }')
        config_h_lines.append(f'#endif // ENCODER_RESOLUTION{postfix}')
    else:
        config_h_lines.append(f'#ifndef ENCODER_RESOLUTIONS{postfix}')
        config_h_lines.append(f'#   define ENCODER_RESOLUTIONS{postfix} {{ { ", ".join(resolutions) } }}')
        config_h_lines.append(f'#endif // ENCODER_RESOLUTIONS{postfix}')


def generate_split_config(kb_info_json, config_h_lines):
    """Generate the config.h lines for split boards."""
    if 'primary' in kb_info_json['split']:
        if kb_info_json['split']['primary'] in ('left', 'right'):
            config_h_lines.append('')
            config_h_lines.append('#ifndef MASTER_LEFT')
            config_h_lines.append('#   ifndef MASTER_RIGHT')
            if kb_info_json['split']['primary'] == 'left':
                config_h_lines.append('#       define MASTER_LEFT')
            elif kb_info_json['split']['primary'] == 'right':
                config_h_lines.append('#       define MASTER_RIGHT')
            config_h_lines.append('#   endif // MASTER_RIGHT')
            config_h_lines.append('#endif // MASTER_LEFT')
        elif kb_info_json['split']['primary'] == 'pin':
            config_h_lines.append('')
            config_h_lines.append('#ifndef SPLIT_HAND_PIN')
            config_h_lines.append('#   define SPLIT_HAND_PIN')
            config_h_lines.append('#endif // SPLIT_HAND_PIN')
        elif kb_info_json['split']['primary'] == 'matrix_grid':
            config_h_lines.append('')
            config_h_lines.append('#ifndef SPLIT_HAND_MATRIX_GRID')
            config_h_lines.append('#   define SPLIT_HAND_MATRIX_GRID {%s}' % (','.join(kb_info_json["split"]["matrix_grid"],)))
            config_h_lines.append('#endif // SPLIT_HAND_MATRIX_GRID')
        elif kb_info_json['split']['primary'] == 'eeprom':
            config_h_lines.append('')
            config_h_lines.append('#ifndef EE_HANDS')
            config_h_lines.append('#   define EE_HANDS')
            config_h_lines.append('#endif // EE_HANDS')

    if 'protocol' in kb_info_json['split'].get('transport', {}):
        if kb_info_json['split']['transport']['protocol'] == 'i2c':
            config_h_lines.append('')
            config_h_lines.append('#ifndef USE_I2C')
            config_h_lines.append('#   define USE_I2C')
            config_h_lines.append('#endif // USE_I2C')

    if 'right' in kb_info_json['split'].get('matrix_pins', {}):
        config_h_lines.append(matrix_pins(kb_info_json['split']['matrix_pins']['right'], '_RIGHT'))

    if 'right' in kb_info_json['split'].get('encoder', {}):
        generate_encoder_config(kb_info_json['split']['encoder']['right'], config_h_lines, '_RIGHT')


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, required=True, help='Keyboard to generate config.h for.')
@cli.argument('-km', '--keymap', arg_only=True, help='Keymap to generate config.h for.')
@cli.subcommand('Used by the make system to generate info_config.h from info.json', hidden=True)
def generate_config_h(cli):
    """Generates the info_config.h file.
    """
    # Determine our keyboard/keymap
    if cli.args.keymap:
        kb_info_json = dotty(keymap_json_config(cli.args.keyboard, cli.args.keymap))
    else:
        kb_info_json = dotty(info_json(cli.args.keyboard))

    # Build the info_config.h file.
    config_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once']

    generate_config_items(kb_info_json, config_h_lines)

    generate_matrix_size(kb_info_json, config_h_lines)

    if 'matrix_pins' in kb_info_json:
        config_h_lines.append(matrix_pins(kb_info_json['matrix_pins']))

    if 'encoder' in kb_info_json:
        generate_encoder_config(kb_info_json['encoder'], config_h_lines)

    if 'split' in kb_info_json:
        generate_split_config(kb_info_json, config_h_lines)

    # Show the results
    dump_lines(cli.args.output, config_h_lines, cli.args.quiet)
