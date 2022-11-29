"""Used by the make system to generate keyboard.h from info.json.
"""
from pathlib import Path

from milc import cli

from qmk.path import normpath
from qmk.info import info_json
from qmk.commands import dump_lines
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.constants import COL_LETTERS, ROW_LETTERS, GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE


def _generate_layouts(keyboard):
    """Generates the layouts.h file.
    """
    # Build the info.json file
    kb_info_json = info_json(keyboard)

    if 'matrix_size' not in kb_info_json:
        cli.log.error(f'{keyboard}: Invalid matrix config.')
        return []

    col_num = kb_info_json['matrix_size']['cols']
    row_num = kb_info_json['matrix_size']['rows']

    lines = []
    for layout_name in kb_info_json['layouts']:
        if kb_info_json['layouts'][layout_name]['c_macro']:
            continue

        if 'matrix' not in kb_info_json['layouts'][layout_name]['layout'][0]:
            cli.log.debug(f'{keyboard}/{layout_name}: No matrix data!')
            continue

        layout_keys = []
        layout_matrix = [['KC_NO' for i in range(col_num)] for i in range(row_num)]

        for i, key in enumerate(kb_info_json['layouts'][layout_name]['layout']):
            row = key['matrix'][0]
            col = key['matrix'][1]
            identifier = 'k%s%s' % (ROW_LETTERS[row], COL_LETTERS[col])

            try:
                layout_matrix[row][col] = identifier
                layout_keys.append(identifier)
            except IndexError:
                key_name = key.get('label', identifier)
                cli.log.error(f'Matrix data out of bounds for layout {layout_name} at index {i} ({key_name}): [{row}, {col}]')
                return []

        lines.append('')
        lines.append('#define %s(%s) {\\' % (layout_name, ', '.join(layout_keys)))

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


@cli.argument('-i', '--include', nargs='?', arg_only=True, help='Optional file to include')
@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, required=True, help='Keyboard to generate keyboard.h for.')
@cli.subcommand('Used by the make system to generate keyboard.h from info.json', hidden=True)
def generate_keyboard_h(cli):
    """Generates the keyboard.h file.
    """
    keyboard_h = cli.args.include
    dd_layouts = _generate_layouts(cli.args.keyboard)
    valid_config = dd_layouts or keyboard_h

    # Build the layouts.h file.
    keyboard_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '#include "quantum.h"']

    keyboard_h_lines.append('')
    keyboard_h_lines.append('// Layout content')
    if dd_layouts:
        keyboard_h_lines.extend(dd_layouts)
    if keyboard_h:
        keyboard_h_lines.append(f'#include "{Path(keyboard_h).name}"')

    # Protect against poorly configured keyboards
    if not valid_config:
        keyboard_h_lines.append('#error("<keyboard>.h is required unless your keyboard uses data-driven configuration. Please rename your keyboard\'s header file to <keyboard>.h")')

    # Show the results
    dump_lines(cli.args.output, keyboard_h_lines, cli.args.quiet)
