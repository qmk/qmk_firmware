#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Compiler for keymap.c files

This scrip will generate a keymap.c file from a simple
markdown file with a specific layout.

Usage:
    python compile_keymap.py INPUT_PATH [OUTPUT_PATH]
"""
from __future__ import division
from __future__ import print_function
from __future__ import absolute_import
from __future__ import unicode_literals

import os
import io
import re
import sys
import json
import unicodedata
import collections
import itertools as it

PY2 = sys.version_info.major == 2

if PY2:
    chr = unichr

KEYBOARD_LAYOUTS = {
    # These map positions in the parsed layout to
    # positions in the LAYOUT_ergodox MATRIX
    'ergodox_ez': [
        [0, 1, 2, 3, 4, 5, 6],
        [38, 39, 40, 41, 42, 43, 44],
        [7, 8, 9, 10, 11, 12, 13],
        [45, 46, 47, 48, 49, 50, 51],
        [14, 15, 16, 17, 18, 19],
        [52, 53, 54, 55, 56, 57],
        [20, 21, 22, 23, 24, 25, 26],
        [58, 59, 60, 61, 62, 63, 64],
        [27, 28, 29, 30, 31],
        [65, 66, 67, 68, 69],
        [32, 33],
        [70, 71],
        [34],
        [72],
        [35, 36, 37],
        [73, 74, 75],
    ]
}

ROW_INDENTS = {'ergodox_ez': [0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 5, 0, 6, 0, 4, 0]}

BLANK_LAYOUTS = [
    # Compact Layout
    """
.------------------------------------.------------------------------------.
|     |    |    |    |    |    |     |     |    |    |    |    |    |     |
!-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
|     |    |    |    |    |    |     |     |    |    |    |    |    |     |
!-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
|     |    |    |    |    |    |-----!-----!    |    |    |    |    |     |
!-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
|     |    |    |    |    |    |     |     |    |    |    |    |    |     |
'-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 |    |    |    |    |    |                     !    |    |    |    |    |
 '------------------------'                     '------------------------'
                        .-----------. .-----------.
                        |     |     | !     |     |
                  .-----+-----+-----! !-----+-----+-----.
                  !     !     |     | !     |     !     !
                  !     !     !-----! !-----!     !     !
                  |     |     |     | !     |     |     |
                  '-----------------' '-----------------'
""",

    # Wide Layout
    """
.---------------------------------------------. .---------------------------------------------.
|       |     |     |     |     |     |       | !       |     |     |     |     |     |       |
!-------+-----+-----+-----+-----+-------------! !-------+-----+-----+-----+-----+-----+-------!
|       |     |     |     |     |     |       | !       |     |     |     |     |     |       |
!-------+-----+-----+-----x-----x-----!       ! !       !-----x-----x-----+-----+-----+-------!
|       |     |     |     |     |     |-------! !-------!     |     |     |     |     |       |
!-------+-----+-----+-----x-----x-----!       ! !       !-----x-----x-----+-----+-----+-------!
|       |     |     |     |     |     |       | !       |     |     |     |     |     |       |
'-------+-----+-----+-----+-----+-------------' '-------------+-----+-----+-----+-----+-------'
 |      |     |     |     |     |                             !     |     |     |     |      |
 '------------------------------'                             '------------------------------'
                              .---------------. .---------------.
                              |       |       | !       |       |
                      .-------+-------+-------! !-------+-------+-------.
                      !       !       |       | !       |       !       !
                      !       !       !-------! !-------!       !       !
                      |       |       |       | !       |       |       |
                      '-----------------------' '-----------------------'
""",
]

DEFAULT_CONFIG = {
    "keymaps_includes": ["keymap_common.h",],
    'filler': "-+.'!:x",
    'separator': "|",
    'default_key_prefix': ["KC_"],
}

SECTIONS = [
    'layout_config',
    'layers',
]

#       Markdown Parsing

ONELINE_COMMENT_RE = re.compile(
    r"""
    ^                       # comment must be at the start of the line
    \s*                     # arbitrary whitespace
    //                      # start of the comment
    (.*)                    # the comment
    $                       # until the end of line
""", re.MULTILINE | re.VERBOSE
)

INLINE_COMMENT_RE = re.compile(
    r"""
    ([\,\"\[\]\{\}\d])      # anythig that might end a expression
    \s+                     # comment must be preceded by whitespace
    //                      # start of the comment
    \s                      # and succeded by whitespace
    (?:[^\"\]\}\{\[]*)      # the comment (except things which might be json)
    $                       # until the end of line
""", re.MULTILINE | re.VERBOSE
)

TRAILING_COMMA_RE = re.compile(
    r"""
    ,                       # the comma
    (?:\s*)                 # arbitrary whitespace
    $                       # only works if the trailing comma is followed by newline
    (\s*)                   # arbitrary whitespace
    ([\]\}])                # end of an array or object
""", re.MULTILINE | re.VERBOSE
)


def loads(raw_data):
    if isinstance(raw_data, bytes):
        raw_data = raw_data.decode('utf-8')

    raw_data = ONELINE_COMMENT_RE.sub(r"", raw_data)
    raw_data = INLINE_COMMENT_RE.sub(r"\1", raw_data)
    raw_data = TRAILING_COMMA_RE.sub(r"\1\2", raw_data)
    return json.loads(raw_data)


def parse_config(path):
    def reset_section():
        section.update({
            'name': section.get('name', ""),
            'sub_name': "",
            'start_line': -1,
            'end_line': -1,
            'code_lines': [],
        })

    def start_section(line_index, line):
        end_section()
        if line.startswith("# "):
            name = line[2:]
        elif line.startswith("## "):
            name = line[3:]
        else:
            name = ""

        name = name.strip().replace(" ", "_").lower()
        if name in SECTIONS:
            section['name'] = name
        else:
            section['sub_name'] = name
        section['start_line'] = line_index

    def end_section():
        if section['start_line'] >= 0:
            if section['name'] == 'layout_config':
                config.update(loads("\n".join(section['code_lines'])))
            elif section['sub_name'].startswith('layer'):
                layer_name = section['sub_name']
                config['layer_lines'][layer_name] = section['code_lines']

        reset_section()

    def amend_section(line_index, line):
        section['end_line'] = line_index
        section['code_lines'].append(line)

    config = DEFAULT_CONFIG.copy()
    config.update({
        'layer_lines': collections.OrderedDict(),
        'macro_ids': {'UM'},
        'unicode_macros': {},
    })

    section = {}
    reset_section()

    with io.open(path, encoding="utf-8") as fh:
        for i, line in enumerate(fh):
            if line.startswith("#"):
                start_section(i, line)
            elif line.startswith("    "):
                amend_section(i, line[4:])
            else:
                # TODO: maybe parse description
                pass

    end_section()
    assert 'layout' in config
    return config


#       header file parsing

IF0_RE = re.compile(r"""
    ^
    #if 0
    $.*?
    #endif
""", re.MULTILINE | re.DOTALL | re.VERBOSE)

COMMENT_RE = re.compile(r"""
    /\*
    .*?
    \*/"
""", re.MULTILINE | re.DOTALL | re.VERBOSE)


def read_header_file(path):
    with io.open(path, encoding="utf-8") as fh:
        data = fh.read()
    data, _ = COMMENT_RE.subn("", data)
    data, _ = IF0_RE.subn("", data)
    return data


def regex_partial(re_str_fmt, flags):
    def partial(*args, **kwargs):
        re_str = re_str_fmt.format(*args, **kwargs)
        return re.compile(re_str, flags)

    return partial


KEYDEF_REP = regex_partial(r"""
    #define
    \s
    (
        (?:{})          # the prefixes
        (?:\w+)         # the key name
    )                   # capture group end
""", re.MULTILINE | re.DOTALL | re.VERBOSE)

ENUM_RE = re.compile(r"""
    (
        enum
        \s\w+\s
        \{
        .*?             # the enum content
        \}
        ;
    )                   # capture group end
""", re.MULTILINE | re.DOTALL | re.VERBOSE)

ENUM_KEY_REP = regex_partial(r"""
    (
        {}              # the prefixes
        \w+             # the key name
    )                   # capture group end
""", re.MULTILINE | re.DOTALL | re.VERBOSE)


def parse_keydefs(config, data):
    prefix_options = "|".join(config['key_prefixes'])
    keydef_re = KEYDEF_REP(prefix_options)
    enum_key_re = ENUM_KEY_REP(prefix_options)
    for match in keydef_re.finditer(data):
        yield match.groups()[0]

    for enum_match in ENUM_RE.finditer(data):
        enum = enum_match.groups()[0]
        for key_match in enum_key_re.finditer(enum):
            yield key_match.groups()[0]


def parse_valid_keys(config, out_path):
    basepath = os.path.abspath(os.path.join(os.path.dirname(out_path)))
    dirpaths = []
    subpaths = []
    while len(subpaths) < 6:
        path = os.path.join(basepath, *subpaths)
        dirpaths.append(path)
        dirpaths.append(os.path.join(path, "tmk_core", "common"))
        dirpaths.append(os.path.join(path, "quantum"))
        subpaths.append('..')

    includes = set(config['keymaps_includes'])
    includes.add("keycode.h")

    valid_keycodes = set()
    for dirpath, include in it.product(dirpaths, includes):
        include_path = os.path.join(dirpath, include)
        if os.path.exists(include_path):
            header_data = read_header_file(include_path)
            valid_keycodes.update(parse_keydefs(config, header_data))
    return valid_keycodes


#       Keymap Parsing


def iter_raw_codes(layer_lines, filler, separator):
    filler_re = re.compile("[" + filler + " ]")
    for line in layer_lines:
        line, _ = filler_re.subn("", line.strip())
        if not line:
            continue
        codes = line.split(separator)
        for code in codes[1:-1]:
            yield code


def iter_indexed_codes(raw_codes, key_indexes):
    key_rows = {}
    key_indexes_flat = []

    for row_index, key_indexes in enumerate(key_indexes):
        for key_index in key_indexes:
            key_rows[key_index] = row_index
        key_indexes_flat.extend(key_indexes)
    assert len(raw_codes) == len(key_indexes_flat)
    for raw_code, key_index in zip(raw_codes, key_indexes_flat):
        # we keep track of the row mostly for layout purposes
        yield raw_code, key_index, key_rows[key_index]


LAYER_CHANGE_RE = re.compile(r"""
    (DF|TG|MO)\(\d+\)
""", re.VERBOSE)

MACRO_RE = re.compile(r"""
    M\(\w+\)
""", re.VERBOSE)

UNICODE_RE = re.compile(r"""
    U[0-9A-F]{4}
""", re.VERBOSE)

NON_CODE = re.compile(r"""
    ^[^A-Z0-9_]$
""", re.VERBOSE)


def parse_uni_code(raw_code):
    macro_id = "UC_" + (unicodedata.name(raw_code).replace(" ", "_").replace("-", "_"))
    code = "M({})".format(macro_id)
    uc_hex = "{:04X}".format(ord(raw_code))
    return code, macro_id, uc_hex


def parse_key_code(raw_code, key_prefixes, valid_keycodes):
    if raw_code in valid_keycodes:
        return raw_code

    for prefix in key_prefixes:
        code = prefix + raw_code
        if code in valid_keycodes:
            return code


def parse_code(raw_code, key_prefixes, valid_keycodes):
    if not raw_code:
        return 'KC_TRNS', None, None

    if LAYER_CHANGE_RE.match(raw_code):
        return raw_code, None, None

    if MACRO_RE.match(raw_code):
        macro_id = raw_code[2:-1]
        return raw_code, macro_id, None

    if UNICODE_RE.match(raw_code):
        hex_code = raw_code[1:]
        return parse_uni_code(chr(int(hex_code, 16)))

    if NON_CODE.match(raw_code):
        return parse_uni_code(raw_code)

    code = parse_key_code(raw_code, key_prefixes, valid_keycodes)
    return code, None, None


def parse_keymap(config, key_indexes, layer_lines, valid_keycodes):
    keymap = {}
    raw_codes = list(iter_raw_codes(layer_lines, config['filler'], config['separator']))
    indexed_codes = iter_indexed_codes(raw_codes, key_indexes)
    key_prefixes = config['key_prefixes']
    for raw_code, key_index, row_index in indexed_codes:
        code, macro_id, uc_hex = parse_code(raw_code, key_prefixes, valid_keycodes)
        # TODO: line numbers for invalid codes
        err_msg = "Could not parse key '{}' on row {}".format(raw_code, row_index)
        assert code is not None, err_msg
        # print(repr(raw_code), repr(code), macro_id, uc_hex)
        if macro_id:
            config['macro_ids'].add(macro_id)
        if uc_hex:
            config['unicode_macros'][macro_id] = uc_hex
        keymap[key_index] = (code, row_index)
    return keymap


def parse_keymaps(config, valid_keycodes):
    keymaps = collections.OrderedDict()
    key_indexes = config.get('key_indexes', KEYBOARD_LAYOUTS[config['layout']])
    # TODO: maybe validate key_indexes

    for layer_name, layer_lines, in config['layer_lines'].items():
        keymaps[layer_name] = parse_keymap(config, key_indexes, layer_lines, valid_keycodes)
    return keymaps


#       keymap.c output

USERCODE = """
// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case L1:
            ergodox_right_led_1_on();
            break;
        case L2:
            ergodox_right_led_2_on();
            break;
        case L3:
            ergodox_right_led_3_on();
            break;
        case L4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case L5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        // case L6:
        //     ergodox_right_led_2_on();
        //     ergodox_right_led_3_on();
        //     break;
        // case L7:
        //     ergodox_right_led_1_on();
        //     ergodox_right_led_2_on();
        //     ergodox_right_led_3_on();
        //     break;
        default:
            ergodox_board_led_off();
            break;
    }
};
"""

MACROCODE = """
#define UC_MODE_WIN 0
#define UC_MODE_LINUX 1
#define UC_MODE_OSX 2

// TODO: allow default mode to be configured
static uint16_t unicode_mode = UC_MODE_WIN;

uint16_t hextokeycode(uint8_t hex) {{
    if (hex == 0x0) {{
        return KC_P0;
    }}
    if (hex < 0xA) {{
        return KC_P1 + (hex - 0x1);
    }}
    return KC_A + (hex - 0xA);
}}

void unicode_action_function(uint16_t hi, uint16_t lo) {{
    switch (unicode_mode) {{
    case UC_MODE_WIN:
        register_code(KC_LALT);

        register_code(KC_PPLS);
        unregister_code(KC_PPLS);

        register_code(hextokeycode((hi & 0xF0) >> 4));
        unregister_code(hextokeycode((hi & 0xF0) >> 4));
        register_code(hextokeycode((hi & 0x0F)));
        unregister_code(hextokeycode((hi & 0x0F)));
        register_code(hextokeycode((lo & 0xF0) >> 4));
        unregister_code(hextokeycode((lo & 0xF0) >> 4));
        register_code(hextokeycode((lo & 0x0F)));
        unregister_code(hextokeycode((lo & 0x0F)));

        unregister_code(KC_LALT);
        break;
    case UC_MODE_LINUX:
        register_code(KC_LCTL);
        register_code(KC_LSFT);

        register_code(KC_U);
        unregister_code(KC_U);

        register_code(hextokeycode((hi & 0xF0) >> 4));
        unregister_code(hextokeycode((hi & 0xF0) >> 4));
        register_code(hextokeycode((hi & 0x0F)));
        unregister_code(hextokeycode((hi & 0x0F)));
        register_code(hextokeycode((lo & 0xF0) >> 4));
        unregister_code(hextokeycode((lo & 0xF0) >> 4));
        register_code(hextokeycode((lo & 0x0F)));
        unregister_code(hextokeycode((lo & 0x0F)));

        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        break;
    case UC_MODE_OSX:
        break;
    }}
}}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {{
    if (!record->event.pressed) {{
        return MACRO_NONE;
    }}
    // MACRODOWN only works in this function
    switch(id) {{
        case UM:
            unicode_mode = (unicode_mode + 1) % 2;
            break;
{macro_cases}
{unicode_macro_cases}
        default:
            break;
    }}
    return MACRO_NONE;
}};
"""

UNICODE_MACRO_TEMPLATE = """
case {macro_id}:
    unicode_action_function(0x{hi:02x}, 0x{lo:02x});
    break;
""".strip()


def unicode_macro_cases(config):
    for macro_id, uc_hex in config['unicode_macros'].items():
        hi = int(uc_hex, 16) >> 8
        lo = int(uc_hex, 16) & 0xFF
        yield UNICODE_MACRO_TEMPLATE.format(macro_id=macro_id, hi=hi, lo=lo)


def iter_keymap_lines(keymap, row_indents=None):
    col_widths = {}
    col = 0
    # first pass, figure out the column widths
    prev_row_index = None
    for code, row_index in keymap.values():
        if row_index != prev_row_index:
            col = 0
            if row_indents:
                col = row_indents[row_index]
        col_widths[col] = max(len(code), col_widths.get(col, 0))
        prev_row_index = row_index
        col += 1

    # second pass, yield the cell values
    col = 0
    prev_row_index = None
    for key_index in sorted(keymap):
        code, row_index = keymap[key_index]
        if row_index != prev_row_index:
            col = 0
            yield "\n"
            if row_indents:
                for indent_col in range(row_indents[row_index]):
                    pad = " " * (col_widths[indent_col] - 4)
                    yield (" /*-*/" + pad)
                col = row_indents[row_index]
        else:
            yield pad
        yield " {}".format(code)
        if key_index < len(keymap) - 1:
            yield ","
            # This will be yielded on the next iteration when
            # we know that we're not at the end of a line.
            pad = " " * (col_widths[col] - len(code))
        prev_row_index = row_index
        col += 1


def iter_keymap_parts(config, keymaps):
    # includes
    for include_path in config['keymaps_includes']:
        yield '#include "{}"\n'.format(include_path)

    yield "\n"

    # definitions
    for i, macro_id in enumerate(sorted(config['macro_ids'])):
        yield "#define {} {}\n".format(macro_id, i)

    yield "\n"

    for i, layer_name in enumerate(config['layer_lines']):
        yield '#define L{0:<3} {0:<5}  // {1}\n'.format(i, layer_name)

    yield "\n"

    # keymaps
    yield "const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\n"

    for i, layer_name in enumerate(config['layer_lines']):
        # comment
        layer_lines = config['layer_lines'][layer_name]
        prefixed_lines = " * " + " * ".join(layer_lines)
        yield "/*\n{} */\n".format(prefixed_lines)

        # keymap codes
        keymap = keymaps[layer_name]
        row_indents = ROW_INDENTS.get(config['layout'])
        keymap_lines = "".join(iter_keymap_lines(keymap, row_indents))
        yield "[L{0}] = LAYOUT_ergodox({1}\n),\n".format(i, keymap_lines)

    yield "};\n\n"

    # macros
    yield MACROCODE.format(
        macro_cases="",
        unicode_macro_cases="\n".join(unicode_macro_cases(config)),
    )

    # TODO: dynamically create blinking lights
    yield USERCODE


def main(argv=sys.argv[1:]):
    if not argv or '-h' in argv or '--help' in argv:
        print(__doc__)
        return 0

    in_path = os.path.abspath(argv[0])
    if not os.path.exists(in_path):
        print("No such file '{}'".format(in_path))
        return 1

    if len(argv) > 1:
        out_path = os.path.abspath(argv[1])
    else:
        dirname = os.path.dirname(in_path)
        out_path = os.path.join(dirname, "keymap.c")

    config = parse_config(in_path)
    valid_keys = parse_valid_keys(config, out_path)
    keymaps = parse_keymaps(config, valid_keys)

    with io.open(out_path, mode="w", encoding="utf-8") as fh:
        for part in iter_keymap_parts(config, keymaps):
            fh.write(part)


if __name__ == '__main__':
    sys.exit(main())
