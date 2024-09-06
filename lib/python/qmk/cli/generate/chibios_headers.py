"""Used by the build system to generate ChibiOS-related header files.
"""
from pathlib import Path
from dotty_dict import dotty

from argcomplete.completers import FilesCompleter
from milc import cli

from qmk.info import info_json
from qmk.json_schema import json_load
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.commands import dump_lines, parse_configurator_json
from qmk.path import normpath, FileType
from qmk.constants import QMK_FIRMWARE, GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE

FIELD_MAPPING = {
    "backlight.pin": "backlight",
    "ws2812.pin": "ws2812",
}

@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), completer=FilesCompleter('.json'), help='A configurator export JSON to be compiled and flashed or a pre-compiled binary firmware file (bin/hex) to be flashed.')
@cli.argument('-o', '--output-dir', arg_only=True, type=normpath, help='Directory to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', arg_only=True, type=keyboard_folder, completer=keyboard_completer, help='Keyboard to generate config.h for.')
@cli.subcommand('Used by the make system to generate ChibiOS configs from info.json', hidden=True)
def generate_chibios_headers(cli):
    """Generates the mcuconf.h, halconf.h, chconf.h, and board.h files whenever necessary.
    """
    # Determine our keyboard/keymap
    if cli.args.filename:
        user_keymap = parse_configurator_json(cli.args.filename)
        kb_info_json = dotty(user_keymap.get('config', {}))
    elif cli.args.keyboard:
        kb_info_json = dotty(info_json(cli.args.keyboard))
    else:
        cli.log.error('You must supply a configurator export or `--keyboard`.')
        cli.subcommands['generate-mcuconf-h'].print_help()
        return False

    # Build the mcuconf.h file.
    lines = {}
    lines['config.h'] = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '']
    lines['mcuconf.h'] = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once',  '', '#include_next <mcuconf.h>', '']
    lines['halconf.h'] = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '']
    lines['chconf.h'] = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '']
    lines['board.h'] = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '', '#include_next <board.h>', '']

    ############################################################################
    # Do stuff here ############################################################
    ############################################################################

    peripherals_json = QMK_FIRMWARE / 'data' / 'mappings' / 'chibios-peripherals' / f'{kb_info_json["processor"].lower()}.hjson'
    if peripherals_json.exists():
        peripherals = json_load(peripherals_json)

        for k, v in FIELD_MAPPING.items():
            if k in kb_info_json and v in peripherals and kb_info_json.get(k) in peripherals[v]:
                periph = peripherals[v][kb_info_json[k]]
                for k2, v2 in lines.items():
                    if k2 in periph:
                        v2.extend(['', f'// {k} = {kb_info_json[k]}', '//---------'])
                        v2.extend(periph[k2])

    # Final lines
    lines['halconf.h'].extend(['', '#include_next <halconf.h>'])
    lines['chconf.h'].extend(['', '#include_next <chconf.h>'])

    # Mark duplicates
    for k, v in lines.items():
        for i, line in enumerate(v):
            if line == '' or line.startswith('//'):
                continue
            if line in v[0:i]:
                v[i] = f'// {v[i]} // Duplicated line'

    # Output the results (skipping duplicates)
    for k, v in lines.items():
        dump_lines(cli.args.output_dir / k, v, cli.args.quiet, remove_dupe_newlines=True)
