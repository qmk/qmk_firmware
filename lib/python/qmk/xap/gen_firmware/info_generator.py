"""This script generates the XAP info.json payload header to be compiled into QMK.
"""
import json
import gzip

from qmk.info import keymap_json
from qmk.commands import get_chunks, dump_lines

from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE


def generate_info(output_file, keyboard, keymap):
    # Build the info.json file
    km_info_json = keymap_json(keyboard, keymap)

    # TODO: Munge to XAP requirements

    # Minify
    str_data = json.dumps(km_info_json, separators=(',', ':'))

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

    dump_lines(output_file, lines)
