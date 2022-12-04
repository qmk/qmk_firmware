"""Used by the make system to generate keyboard.h from info.json.
"""
from milc import cli

from qmk.info import info_json
from qmk.commands import dump_lines
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.path import normpath
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE


def would_populate_layout_h(keyboard):
    """Detect if a given keyboard is doing data driven layouts
    """
    # Build the info.json file
    kb_info_json = info_json(keyboard)

    if 'matrix_size' not in kb_info_json:
        cli.log.error(f'{keyboard}: Invalid matrix config.')
        return []

    col_num = kb_info_json['matrix_size']['cols']
    row_num = kb_info_json['matrix_size']['rows']

    lines = []
    for layout_name, layout_data in kb_info_json['layouts'].items():
        if layout_data['c_macro']:
            continue

        if not all('matrix' in key_data for key_data in layout_data['layout']):
            cli.log.debug(f'{keyboard}/{layout_name}: No or incomplete matrix data!')
            continue

        layout_keys = []
        layout_matrix = [['KC_NO'] * col_num for _ in range(row_num)]

        for index, key_data in enumerate(layout_data['layout']):
            row, col = key_data['matrix']
            identifier = f'k{ROW_LETTERS[row]}{COL_LETTERS[col]}'

            try:
                layout_matrix[row][col] = identifier
                layout_keys.append(identifier)
            except IndexError:
                key_name = key_data.get('label', identifier)
                cli.log.error(f'{keyboard}/{layout_name}: Matrix data out of bounds at index {index} ({key_name}): [{row}, {col}]')
                return []

        lines.append('')
        lines.append(f'#define {layout_name}({", ".join(layout_keys)}) {{ \\')

        rows = ', \\\n'.join(['\t {' + ', '.join(row) + '}' for row in layout_matrix])
        rows += ' \\'
        lines.append(rows)
        lines.append('}')

    for alias, target in kb_info_json.get('layout_aliases', {}).items():
        lines.append('')
        lines.append(f'#ifndef {alias}')
        lines.append(f'#   define {alias} {target}')
        lines.append('#endif')

    return lines


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, required=True, help='Keyboard to generate keyboard.h for.')
@cli.subcommand('Used by the make system to generate keyboard.h from info.json', hidden=True)
def generate_keyboard_h(cli):
    """Generates the keyboard.h file.
    """
    has_layout_h = would_populate_layout_h(cli.args.keyboard)

    # Build the layouts.h file.
    keyboard_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '#include "quantum.h"']

    if not has_layout_h:
        keyboard_h_lines.append('#error("<keyboard>.h is only optional for data driven keyboards - kb.h == bad times")')

    # Show the results
    dump_lines(cli.args.output, keyboard_h_lines, cli.args.quiet)
