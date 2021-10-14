#!/usr/bin/env python

import argparse
import pycparser
import re

class KeymapBeautifier:
    justify_toward_center = False
    filename_in = None
    filename_out = None
    output_layout = None
    output = None

    column_max_widths = {}

    KEY_ALIASES = {
        "KC_TRANSPARENT": "_______",
        "KC_TRNS": "_______",
        "KC_NO": "XXXXXXX",
    }
    KEYMAP_START = 'const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {\n'
    KEYMAP_END = '};\n'
    KEYMAP_START_REPLACEMENT = "const int keymaps[]={\n"
    KEY_CHART = """
    /*
     * ,--------------------------------------------------.    ,--------------------------------------------------.
     * |    0   |   1  |   2  |   3  |   4  |   5  |  6   |    |  38  |  39  |  40  |  41  |  42  |  43  |   44   |
     * |--------+------+------+------+------+------+------|    |------+------+------+------+------+------+--------|
     * |    7   |   8  |   9  |  10  |  11  |  12  |  13  |    |  45  |  46  |  47  |  48  |  49  |  50  |   51   |
     * |--------+------+------+------+------+------|      |    |      |------+------+------+------+------+--------|
     * |   14   |  15  |  16  |  17  |  18  |  19  |------|    |------|  52  |  53  |  54  |  55  |  56  |   57   |
     * |--------+------+------+------+------+------|  26  |    |  58  |------+------+------+------+------+--------|
     * |   20   |  21  |  22  |  23  |  24  |  25  |      |    |      |  59  |  60  |  61  |  62  |  63  |   64   |
     * `--------+------+------+------+------+-------------'    `-------------+------+------+------+------+--------'
     *   |  27  |  28  |  29  |  30  |  31  |                                |  65  |  66  |  67  |  68  |  69  |
     *   `----------------------------------'                                `----------------------------------'
     *                                       ,-------------.  ,-------------.
     *                                       |  32  |  33  |  |  70  |  71  |
     *                                ,------+------+------|  |------+------+------.
     *                                |      |      |  34  |  |  72  |      |      |
     *                                |  35  |  36  |------|  |------|  74  |  75  |
     *                                |      |      |  37  |  |  73  |      |      |
     *                                `--------------------'  `--------------------'
     */
"""
    KEY_COORDINATES = {
        'LAYOUT_ergodox': [
            # left hand
            (0,0), (0,1), (0,2), (0,3), (0,4), (0,5), (0,6),
            (1,0), (1,1), (1,2), (1,3), (1,4), (1,5), (1,6),
            (2,0), (2,1), (2,2), (2,3), (2,4), (2,5),
            (3,0), (3,1), (3,2), (3,3), (3,4), (3,5), (3,6),
            (4,0), (4,1), (4,2), (4,3), (4,4),
            # left thumb
                                               (5,5), (5,6),
                                                      (6,6),
                                        (7,4), (7,5), (7,6),
            # right hand
             (8,0),  (8,1),  (8,2),  (8,3),  (8,4),  (8,5),  (8,6),
             (9,0),  (9,1),  (9,2),  (9,3),  (9,4),  (9,5),  (9,6),
                    (10,1), (10,2), (10,3), (10,4), (10,5), (10,6),
            (11,0), (11,1), (11,2), (11,3), (11,4), (11,5), (11,6),
                            (12,2), (12,3), (12,4), (12,5), (12,6),
            # right thumb
            (13,0), (13,1),
            (14,0),
            (15,0), (15,1), (15,2)
        ],
        'LAYOUT_ergodox_pretty': [
            # left hand and right hand
            (0,0), (0,1), (0,2), (0,3), (0,4), (0,5), (0,6),   (0,7), (0,8), (0,9), (0,10), (0,11), (0,12), (0,13),
            (1,0), (1,1), (1,2), (1,3), (1,4), (1,5), (1,6),   (1,7), (1,8), (1,9), (1,10), (1,11), (1,12), (1,13),
            (2,0), (2,1), (2,2), (2,3), (2,4), (2,5),                 (2,8), (2,9), (2,10), (2,11), (2,12), (2,13),
            (3,0), (3,1), (3,2), (3,3), (3,4), (3,5), (3,6),   (3,7), (3,8), (3,9), (3,10), (3,11), (3,12), (3,13),
            (4,0), (4,1), (4,2), (4,3), (4,4),                               (4,9), (4,10), (4,11), (4,12), (4,13),

            # left thumb and right thumb
                                               (5,5), (5,6),   (5,7), (5,8),
                                                      (6,6),   (6,7),
                                        (7,4), (7,5), (7,6),   (7,7), (7,8), (7,9)
        ],
    }
    current_converted_KEY_COORDINATES = []

    # each column is aligned within each group (tuples of row indexes are inclusive)
    KEY_ROW_GROUPS = {
        'LAYOUT_ergodox': [(0,4),(5,7),(8,12),(13,15)],
        'LAYOUT_ergodox_pretty': [(0,7)],
        #'LAYOUT_ergodox_pretty': [(0,5),(6,7)],
        #'LAYOUT_ergodox_pretty': [(0,3),(4,4),(5,7)],
        #'LAYOUT_ergodox_pretty': [(0,4),(5,7)],
    }


    INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox = [
         0, 1, 2, 3, 4, 5, 6,  38,39,40,41,42,43,44,
         7, 8, 9,10,11,12,13,  45,46,47,48,49,50,51,
        14,15,16,17,18,19,        52,53,54,55,56,57,
        20,21,22,23,24,25,26,  58,59,60,61,62,63,64,
        27,28,29,30,31,              65,66,67,68,69,
                       32,33,  70,71,
                          34,  72,
                    35,36,37,  73,74,75,
    ]


    def index_conversion_map_reversed(self, conversion_map):
        return [conversion_map.index(i) for i in range(len(conversion_map))]


    def __init__(self, source_code = "",  output_layout="LAYOUT_ergodox", justify_toward_center = False):
        self.output_layout = output_layout
        self.justify_toward_center = justify_toward_center
        # determine the conversion map
        #if input_layout == self.output_layout:
        #    conversion_map = [i for i in range(len(self.INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox))]
        #conversion_map = self.INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox
        if self.output_layout == "LAYOUT_ergodox_pretty":
            index_conversion_map = self.index_conversion_map_reversed(self.INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox)
        else:
            index_conversion_map = list(range(len(self.INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox)))
        self.current_converted_KEY_COORDINATES = [
            self.KEY_COORDINATES[self.output_layout][index_conversion_map[i]]
            for i in range(len(self.KEY_COORDINATES[self.output_layout]))
        ]

        self.output = self.beautify_source_code(source_code)

    def beautify_source_code(self, source_code):
        # to keep it simple for the parser, we only use the parser to parse the key definition part
        src = {
            "before": [],
            "keys": [],
            "after": [],
        }

        current_section = "before"
        for line in source_code.splitlines(True):
            if current_section == 'before' and line == self.KEYMAP_START:
                src[current_section].append("\n")
                current_section = 'keys'
                src[current_section].append(self.KEYMAP_START_REPLACEMENT)
                continue
            elif current_section == 'keys' and line == self.KEYMAP_END:
                src[current_section].append(self.KEYMAP_END)
                current_section = 'after'
                continue
            src[current_section].append(line)
        output_lines = src['before'] + self.beautify_keys_section("".join(src['keys'])) + src['after']
        return "".join(output_lines)

    def beautify_keys_section(self, src):
        parsed = self.parser(src)
        layer_output = []

        keymap = parsed.children()[0]
        layers = keymap[1]
        for layer in layers.init.exprs:
            input_layout = layer.expr.name.name

            key_symbols = self.layer_expr(layer)
            # re-order keys from input_layout to regular layout
            if input_layout == "LAYOUT_ergodox_pretty":
                key_symbols = [key_symbols[i] for i in self.index_conversion_map_reversed(self.INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox)]

            padded_key_symbols = self.pad_key_symbols(key_symbols, input_layout)
           
            layer_identifier = None
            if hasattr(layer.name[0], "value"):
                layer_identifier = layer.name[0].value
            elif hasattr(layer.name[0], "name"):
                layer_identifier = layer.name[0].name
            else:
                raise AttributeError("Layer is missing both index and name (e.g., [BASE] = LAYOUT_ergodox(...))")

            current_pretty_output_layer = self.pretty_output_layer(layer_identifier, padded_key_symbols)
            # strip trailing spaces from padding
            layer_output.append(re.sub(r" +\n", "\n", current_pretty_output_layer))

        return [self.KEYMAP_START + "\n",
                self.KEY_CHART + "\n",
                ",\n\n".join(layer_output) + "\n",
                self.KEYMAP_END + "\n"]

    def get_row_group(self, row):
        for low, high in self.KEY_ROW_GROUPS[self.output_layout]:
            if low <= row <= high:
                return (low, high)
        raise Exception("Cannot find row groups in KEY_ROW_GROUPS")


    def calculate_column_max_widths(self, key_symbols):
        # calculate the max width for each column
        self.column_max_widths = {}
        for i in range(len(key_symbols)):
            row_index, column_index = self.current_converted_KEY_COORDINATES[i]
            row_group = self.get_row_group(row_index)
            if (row_group, column_index) in self.column_max_widths:
                self.column_max_widths[(row_group, column_index)] = max(self.column_max_widths[(row_group, column_index)], len(key_symbols[i]))
            else:
                self.column_max_widths[(row_group, column_index)] = len(key_symbols[i])


    def pad_key_symbols(self, key_symbols, input_layout, just='left'):
        self.calculate_column_max_widths(key_symbols)

        padded_key_symbols = []
        # pad each key symbol
        for i in range(len(key_symbols)):
            key = key_symbols[i]
            # look up column coordinate to determine number of spaces to pad
            row_index, column_index = self.current_converted_KEY_COORDINATES[i]
            row_group = self.get_row_group(row_index)
            if just == 'left':
                padded_key_symbols.append(key.ljust(self.column_max_widths[(row_group, column_index)]))
            else:
                padded_key_symbols.append(key.rjust(self.column_max_widths[(row_group, column_index)]))
        return padded_key_symbols


    layer_keys_pointer = 0
    layer_keys = None
    def grab_next_n_columns(self, n_columns, input_layout, layer_keys = None, from_beginning = False):
        if layer_keys:
            self.layer_keys = layer_keys
        if from_beginning:
            self.layer_keys_pointer = 0

        begin = self.layer_keys_pointer
        return self.layer_keys[self.layer_keys_pointer-n_keys:self.layer_keys_pointer]

    key_coordinates_counter = 0
    def get_padded_line(self, source_keys, key_from, key_to, just="left"):
        if just == "right":
            keys = [k.strip().rjust(len(k)) for k in source_keys[key_from:key_to]]
        else:
            keys = [k for k in source_keys[key_from:key_to]]

        from_row, from_column = self.KEY_COORDINATES[self.output_layout][self.key_coordinates_counter]
        row_group = self.get_row_group(from_row)
        self.key_coordinates_counter += key_to - key_from
        columns_before_key_from = sorted([col for row, col in self.KEY_COORDINATES[self.output_layout] if row == from_row and col < from_column])
        # figure out which columns in this row needs padding; only pad empty columns to the right of an existing column
        columns_to_pad = { c: True for c in range(from_column) }
        if columns_before_key_from:
            for c in range(max(columns_before_key_from)+1):
                columns_to_pad[c] = False

        # for rows with fewer columns that don't start with column 0, we need to insert leading spaces
        spaces = 0
        for c, v in columns_to_pad.items():
            if not v:
                continue
            if (row_group,c) in self.column_max_widths:
                spaces += self.column_max_widths[(row_group,c)] + len(", ")
            else:
                spaces += 0
        return " " * spaces + ", ".join(keys) + ","

    def pretty_output_layer(self, layer, keys):
        self.key_coordinates_counter = 0
        if self.output_layout == "LAYOUT_ergodox":
            formatted_key_symbols = """
// left hand

{}
{}
{}
{}
{}

// left thumb

{}
{}
{}

// right hand

{}
{}
{}
{}
{}

// right thumb

{}
{}
{}
""".format(
            # left hand
            self.get_padded_line(keys,  0,  7, just="left"),
            self.get_padded_line(keys,  7, 14, just="left"),
            self.get_padded_line(keys, 14, 20, just="left"),
            self.get_padded_line(keys, 20, 27, just="left"),
            self.get_padded_line(keys, 27, 32, just="left"),
            # left thumb
            self.get_padded_line(keys, 32, 34, just="left"),
            self.get_padded_line(keys, 34, 35, just="left"),
            self.get_padded_line(keys, 35, 38, just="left"),
            # right hand
            self.get_padded_line(keys, 38, 45, just="left"),
            self.get_padded_line(keys, 45, 52, just="left"),
            self.get_padded_line(keys, 52, 58, just="left"),
            self.get_padded_line(keys, 58, 65, just="left"),
            self.get_padded_line(keys, 65, 70, just="left"),
            # right thumb
            self.get_padded_line(keys, 70, 72, just="left"),
            self.get_padded_line(keys, 72, 73, just="left"),
            self.get_padded_line(keys, 73, 76, just="left"),
            )
        elif self.output_layout == "LAYOUT_ergodox_pretty":
            left_half_justification = "right" if self.justify_toward_center else "left"
            formatted_key_symbols = """
{}      {}
{}      {}
{}      {}
{}      {}
{}      {}

{}      {}
{}      {}
{}      {}
""".format(
                self.get_padded_line(keys,  0,  7, just=left_half_justification), self.get_padded_line(keys, 38, 45, just="left"),
                self.get_padded_line(keys,  7, 14, just=left_half_justification), self.get_padded_line(keys, 45, 52, just="left"),
                self.get_padded_line(keys, 14, 20, just=left_half_justification), self.get_padded_line(keys, 52, 58, just="left"),
                self.get_padded_line(keys, 20, 27, just=left_half_justification), self.get_padded_line(keys, 58, 65, just="left"),
                self.get_padded_line(keys, 27, 32, just=left_half_justification), self.get_padded_line(keys, 65, 70, just="left"),

                self.get_padded_line(keys, 32, 34, just=left_half_justification), self.get_padded_line(keys, 70, 72, just="left"),
                self.get_padded_line(keys, 34, 35, just=left_half_justification), self.get_padded_line(keys, 72, 73, just="left"),
                self.get_padded_line(keys, 35, 38, just=left_half_justification), self.get_padded_line(keys, 73, 76, just="left"),

                )
        else:
            formatted_key_symbols = ""

        # rid of the trailing comma
        formatted_key_symbols = formatted_key_symbols[0:len(formatted_key_symbols)-2] + "\n"
        s = "[{}] = {}({})".format(layer, self.output_layout, formatted_key_symbols)
        return s

    # helper functions for pycparser
    def parser(self, src):
        src = self.comment_remover(src)
        return pycparser.CParser().parse(src)
    def comment_remover(self, text):
        # remove comments since pycparser cannot deal with them
        # credit: https://stackoverflow.com/a/241506
        def replacer(match):
            s = match.group(0)
            if s.startswith('/'):
                return " " # note: a space and not an empty string
            else:
                return s
        pattern = re.compile(
            r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
            re.DOTALL | re.MULTILINE
        )
        return re.sub(pattern, replacer, text)

    def function_expr(self, f):
        name = f.name.name
        args = []
        for arg in f.args.exprs:
            if type(arg) is pycparser.c_ast.Constant:
                args.append(arg.value)
            elif type(arg) is pycparser.c_ast.ID:
                args.append(arg.name)
            elif type(arg) is pycparser.c_ast.FuncCall:
                args.append(self.function_expr(arg))
        return "{}({})".format(name, ",".join(args))

    def key_expr(self, raw):
        if type(raw) is pycparser.c_ast.ID:
            if raw.name in self.KEY_ALIASES:
                return self.KEY_ALIASES[raw.name]
            return raw.name
        elif type(raw) is pycparser.c_ast.FuncCall:
            return self.function_expr(raw)

    def layer_expr(self, layer):
        transformed = [self.key_expr(k) for k in layer.expr.args.exprs]
        return transformed


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Beautify keymap.c downloaded from ErgoDox-Ez Configurator for easier customization.")
    parser.add_argument("input_filename", help="input file: c source code file that has the layer keymaps")
    parser.add_argument("-o", "--output-filename", help="output file: beautified c filename. If not given, output to STDOUT.")
    parser.add_argument("-p", "--pretty-output-layout", action="store_true", help="use LAYOUT_ergodox_pretty for output instead of LAYOUT_ergodox")
    parser.add_argument("-c", "--justify-toward-center", action="store_true", help="for LAYOUT_ergodox_pretty, align right for the left half, and align left for the right half. Default is align left for both halves.")
    args = parser.parse_args()
    if args.pretty_output_layout:
        output_layout="LAYOUT_ergodox_pretty"
    else:
        output_layout="LAYOUT_ergodox"
    with open(args.input_filename) as f:
        source_code = f.read()
    result = KeymapBeautifier(source_code, output_layout=output_layout, justify_toward_center=args.justify_toward_center).output
    if args.output_filename:
        with open(args.output_filename, "w") as f:
            f.write(result)
    else:
        print(result)

