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

    for layout_name in kb_info_json['layouts']:
        if kb_info_json['layouts'][layout_name]['c_macro']:
            continue

        if 'matrix' not in kb_info_json['layouts'][layout_name]['layout'][0]:
            cli.log.debug('%s/%s: No matrix data!', keyboard, layout_name)
            continue

        return True

    return False


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
