"""Used by the make system to generate keyboard.c from info.json.
"""
from milc import cli

from qmk.info import info_json
from qmk.commands import dump_lines
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.path import normpath
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE


def _gen_led_configs(info_data):
    lines = []

    if 'layout' in info_data.get('rgb_matrix', {}):
        lines.extend(_gen_led_config(info_data, 'rgb_matrix'))

    if 'layout' in info_data.get('led_matrix', {}):
        lines.extend(_gen_led_config(info_data, 'led_matrix'))

    return lines


def _gen_led_config(info_data, config_type):
    """Convert info.json content to g_led_config
    """
    cols = info_data['matrix_size']['cols']
    rows = info_data['matrix_size']['rows']

    lines = []

    matrix = [['NO_LED'] * cols for _ in range(rows)]
    pos = []
    flags = []

    led_layout = info_data[config_type]['layout']
    for index, led_data in enumerate(led_layout):
        if 'matrix' in led_data:
            row, col = led_data['matrix']
            matrix[row][col] = str(index)
        pos.append(f'{{{led_data.get("x", 0)}, {led_data.get("y", 0)}}}')
        flags.append(str(led_data.get('flags', 0)))

    if config_type == 'rgb_matrix':
        lines.append('#ifdef RGB_MATRIX_ENABLE')
        lines.append('#include "rgb_matrix.h"')
    elif config_type == 'led_matrix':
        lines.append('#ifdef LED_MATRIX_ENABLE')
        lines.append('#include "led_matrix.h"')

    lines.append('__attribute__ ((weak)) led_config_t g_led_config = {')
    lines.append('  {')
    for line in matrix:
        lines.append(f'    {{ {", ".join(line)} }},')
    lines.append('  },')
    lines.append(f'  {{ {", ".join(pos)} }},')
    lines.append(f'  {{ {", ".join(flags)} }},')
    lines.append('};')
    lines.append('#endif')
    lines.append('')

    return lines


def _gen_matrix_mask(info_data):
    """Convert info.json content to matrix_mask
    """
    cols = info_data['matrix_size']['cols']
    rows = info_data['matrix_size']['rows']

    # Default mask to everything disabled
    mask = [['0'] * cols for _ in range(rows)]

    # Mirror layout macros squashed on top of each other
    for layout_name, layout_data in info_data['layouts'].items():
        for key_data in layout_data['layout']:
            row, col = key_data['matrix']
            if row >= rows or col >= cols:
                cli.log.error(f'Skipping matrix_mask due to {layout_name} containing invalid matrix values')
                return []
            mask[row][col] = '1'

    lines = []
    lines.append('#ifdef MATRIX_MASKED')
    lines.append('__attribute__((weak)) const matrix_row_t matrix_mask[] = {')
    for i in range(rows):
        lines.append(f'    0b{"".join(reversed(mask[i]))},')
    lines.append('};')
    lines.append('#endif')

    return lines


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, required=True, help='Keyboard to generate keyboard.c for.')
@cli.subcommand('Used by the make system to generate keyboard.c from info.json', hidden=True)
def generate_keyboard_c(cli):
    """Generates the keyboard.h file.
    """
    kb_info_json = info_json(cli.args.keyboard)

    # Build the layouts.h file.
    keyboard_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#include QMK_KEYBOARD_H', '']

    keyboard_h_lines.extend(_gen_led_configs(kb_info_json))
    keyboard_h_lines.extend(_gen_matrix_mask(kb_info_json))

    # Show the results
    dump_lines(cli.args.output, keyboard_h_lines, cli.args.quiet)
