"""Used by the make system to generate LUFA Keyboard.h from info.json
"""
from dotty_dict import dotty
from milc import cli

from qmk.decorators import automagic_keyboard
from qmk.info import info_json
from qmk.path import normpath
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.commands import dump_lines
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', required=True, arg_only=True, type=keyboard_folder, completer=keyboard_completer, help='Keyboard to generate LUFA Keyboard.h for.')
@cli.subcommand('Used by the make system to generate LUFA Keyboard.h from info.json', hidden=True)
@automagic_keyboard
def generate_dfu_header(cli):
    """Generates the Keyboard.h file.
    """
    # Build the Keyboard.h file.
    kb_info_json = dotty(info_json(cli.args.keyboard))

    keyboard_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once']
    keyboard_h_lines.append(f'#define MANUFACTURER "{kb_info_json["manufacturer"]}"')
    keyboard_h_lines.append(f'#define PRODUCT "{kb_info_json["keyboard_name"]} Bootloader"')

    # Optional
    if 'qmk_lufa_bootloader.esc_output' in kb_info_json:
        keyboard_h_lines.append(f'#define QMK_ESC_OUTPUT {kb_info_json["qmk_lufa_bootloader.esc_output"]}')
    if 'qmk_lufa_bootloader.esc_input' in kb_info_json:
        keyboard_h_lines.append(f'#define QMK_ESC_INPUT {kb_info_json["qmk_lufa_bootloader.esc_input"]}')
    if 'qmk_lufa_bootloader.led' in kb_info_json:
        keyboard_h_lines.append(f'#define QMK_LED {kb_info_json["qmk_lufa_bootloader.led"]}')
    if 'qmk_lufa_bootloader.speaker' in kb_info_json:
        keyboard_h_lines.append(f'#define QMK_SPEAKER {kb_info_json["qmk_lufa_bootloader.speaker"]}')

    # Show the results
    dump_lines(cli.args.output, keyboard_h_lines, cli.args.quiet)
