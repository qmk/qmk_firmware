"""This script generates the XAP protocol generated sources to be compiled into QMK firmware.
"""
import json
import gzip

from milc import cli

from qmk.path import normpath
from qmk.info import info_json
from qmk.commands import get_chunks, dump_lines
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.xap.gen_firmware.inline_generator import generate_inline
from qmk.xap.gen_firmware.header_generator import generate_header

from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.subcommand('Generates the XAP protocol include.', hidden=False if cli.config.user.developer else True)
def xap_generate_qmk_inc(cli):
    """Generates the XAP protocol inline codegen file, generated during normal build.
    """
    generate_inline(cli.args.output)


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Name of the keyboard')
@cli.subcommand('Generates the XAP protocol include.', hidden=False if cli.config.user.developer else True)
def xap_generate_qmk_h(cli):
    """Generates the XAP protocol header file, generated during normal build.
    """
    # Determine our keyboard
    if not cli.args.keyboard:
        cli.log.error('Missing parameter: --keyboard')
        cli.subcommands['xap-generate-qmk-h'].print_help()
        return False
    generate_header(cli.args.output, cli.args.keyboard)


@cli.argument('-o', '--output', type=normpath, help='File to write to')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Name of the keyboard')
@cli.argument('-km', '--keymap', help='The keymap\'s name')
@cli.subcommand('Generates the XAP info.json payload include.', hidden=False if cli.config.user.developer else True)
def xap_generate_info_h(cli):
    """Generates the XAP info.json payload header file, generated during normal build.
    """
    # Determine our keyboard
    if not cli.args.keyboard:
        cli.log.error('Missing parameter: --keyboard')
        cli.subcommands['xap-generate-info-h'].print_help()
        return False

    # TODO: merge in keymap level content
    # Build the info.json file
    kb_info_json = info_json(cli.args.keyboard)

    # Minify
    str_data = json.dumps(kb_info_json, separators=(',', ':'))

    # Compress
    compressed = gzip.compress(str_data.encode("utf-8"), compresslevel=9)

    # split into lines to match xxd output
    hex_array = ["0x{:02X}".format(b) for b in compressed]
    data_len = len(hex_array)

    data = ""
    for chunk in get_chunks(hex_array, 12):
        data += f'  {", ".join(chunk)},\n'

    lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '']

    # Gen output file
    lines.append('unsigned char info_json_gz[] = {')
    lines.append(data)
    lines.append('};')
    lines.append(f'unsigned int info_json_gz_len = {data_len};')

    dump_lines(cli.args.output, lines)
