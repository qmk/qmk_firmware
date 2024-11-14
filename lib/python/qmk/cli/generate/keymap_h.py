from argcomplete.completers import FilesCompleter

from milc import cli

import qmk.path
from qmk.commands import dump_lines
from qmk.commands import parse_configurator_json
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE


def _generate_keycodes_function(keymap_json):
    """Generates keymap level keycodes.
    """
    lines = []
    lines.append('enum keymap_keycodes {')

    for index, item in enumerate(keymap_json.get('keycodes', [])):
        key = item["key"]
        if index == 0:
            lines.append(f'  {key} = QK_USER_0,')
        else:
            lines.append(f'  {key},')

    lines.append('};')

    for item in keymap_json.get('keycodes', []):
        key = item["key"]
        for alias in item.get("aliases", []):
            lines.append(f'#define {alias} {key}')

    return lines


@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', type=qmk.path.FileType('r'), arg_only=True, completer=FilesCompleter('.json'), help='Configurator JSON file')
@cli.subcommand('Creates a keymap.h from a QMK Configurator export.')
def generate_keymap_h(cli):
    """Creates a keymap.h from a QMK Configurator export
    """
    if cli.args.output and cli.args.output.name == '-':
        cli.args.output = None

    keymap_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '// clang-format off']

    keymap_json = parse_configurator_json(cli.args.filename)

    if 'keycodes' in keymap_json and keymap_json['keycodes'] is not None:
        keymap_h_lines += _generate_keycodes_function(keymap_json)

    dump_lines(cli.args.output, keymap_h_lines, cli.args.quiet)
