"""This script generates the XAP info.json payload header to be compiled into QMK.
"""
import json
import gzip
from pathlib import Path

from qmk.info import keymap_json
from qmk.commands import get_chunks, dump_lines
from qmk.json_schema import deep_update, json_load

from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE


def _build_info(keyboard, keymap):
    """Build the xap version of info.json
    """
    defaults_json = json_load(Path('data/mappings/xap_defaults.json'))
    km_info_json = keymap_json(keyboard, keymap)

    info_json = {}
    deep_update(info_json, defaults_json)
    deep_update(info_json, km_info_json)

    # TODO: Munge to XAP requirements
    del info_json['config_h_features']
    del info_json['keymaps']
    del info_json['parse_errors']
    del info_json['parse_warnings']
    del info_json['usb']['device_ver']
    for layout in info_json['layouts'].values():
        del layout['filename']
        del layout['c_macro']
        for item in layout['layout']:
            item.pop('label', None)

    return info_json


def generate_blob(output_file, keyboard, keymap):
    """Generate XAP payload
    """
    info_json = _build_info(keyboard, keymap)

    # Minify
    str_data = json.dumps(info_json, separators=(',', ':'))

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
    lines.append('static const unsigned char config_blob_gz[] PROGMEM = {')
    lines.append(data)
    lines.append('};')
    lines.append(f'#define CONFIG_BLOB_GZ_LEN {data_len}')

    dump_lines(output_file, lines)
