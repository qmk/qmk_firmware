"""Used by the make system to generate header.
"""
from fnvhash import fnv1a_32

from milc import cli

from qmk.commands import dump_lines
from qmk.keymap import locate_keymap
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.path import normpath
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, required=True, help='Keyboard to generate header for.')
@cli.argument('-km', '--keymap', arg_only=True, required=True, help='Keymap to generate header for.')
@cli.subcommand('Used by the make system to generate header', hidden=True)
def generate_keymap_hash(cli):
    # Build the header file.
    header_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once']

    keymap_folder = locate_keymap(cli.args.keyboard, cli.args.keymap).parent

    keymap_files = list(keymap_folder.glob('**/*'))
    keymap_files.sort()

    content = ""
    for file in keymap_files:
        content += file.read_text(encoding='utf-8')

    val = fnv1a_32(bytes(content, 'utf-8'))
    header_lines.append(f'#define KEYMAP_HASH 0x{val:08X}ul')

    # Show the results
    dump_lines(cli.args.output, header_lines, cli.args.quiet)
