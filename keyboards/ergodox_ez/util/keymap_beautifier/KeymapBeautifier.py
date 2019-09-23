#!/usr/bin/env python

import argparse
import pycparser
import re

class KeymapBeautifier:
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
    #
    KEY_ROW_GROUPS = {
        'LAYOUT_ergodox': [(0,4),(5,7),(8,12),(13,15)],
        'LAYOUT_ergodox_pretty': [(0,4),(5,7)],
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


    def __init__(self, filename_in = None, filename_out = None, output_layout="LAYOUT_ergodox"):
        self.filename_in = filename_in
        self.filename_out = filename_out
        self.output_layout = output_layout

        self.output = self.beautify_src_file(filename_in)
        if filename_out:
            with open(filename_out, "w") as f:
                f.write(self.output)

    def beautify_src_file(self, filename):
        # we only use the parser to parse the key definition part
        # (we don't want to complicate the parsing with the pre-processor)
        src = {
            "before": [],
            "keys": [],
            "after": [],
        }

        with open(filename) as f:
            current_section = "before"
            for line in f:
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
        return src['before'] + self.beautify_keys_section("".join(src['keys'])) + src['after']

    def beautify_keys_section(self, src):
        parsed = self.parser(src)
        layer_output = []

        keymap = parsed.children()[0]
        layers = keymap[1]
        for layer in layers.init.exprs:
            input_layout = layer.expr.name.name
            #print(input_layout)

            key_symbols = self.layer_expr(layer)
            # re-order keys to output_layout
            # TODO support pretty layout
            if input_layout != self.output_layout:
                # converstion needed
                if input_layout == "LAYOUT_ergodox_pretty":
                    key_symbols = [key_symbols[i] for i in self.INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox]
                else:
                    # default input_layout is LAYOUT_ergodox
                    key_symbols = [key_symbols[i] for i in self.index_conversion_map_reversed(self.INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox)]

            padded_key_symbols = self.pad_key_symbols(key_symbols, input_layout)
            layer_output.append(self.pretty_output_layer(layer.name[0].value, padded_key_symbols))

            # TODO remove this
            return [",\n\n".join(layer_output) + "\n"]

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
        for i in range(len(key_symbols)):
            row_index, column_index = self.KEY_COORDINATES[self.output_layout][i]
            row_group = self.get_row_group(row_index)
            if (row_group, column_index) in self.column_max_widths:
                self.column_max_widths[(row_group, column_index)] = max(self.column_max_widths[(row_group, column_index)], len(key_symbols[i]))
            else:
                self.column_max_widths[(row_group, column_index)] = len(key_symbols[i])


    def pad_key_symbols(self, key_symbols, input_layout):
        self.calculate_column_max_widths(key_symbols)
        #print(self.column_max_widths)

        # determine the conversion map
        if input_layout == self.output_layout:
            conversion_map = [i for i in range(len(self.INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox))]
        elif input_layout == "LAYOUT_ergodox_pretty":
            conversion_map = self.INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox
        else:
            conversion_map = self.index_conversion_map_reversed(self.INDEX_CONVERSTION_LAYOUT_ergodox_pretty_to_LAYOUT_ergodox)

        padded_key_symbols = []
        # pad each key symbol
        for i in range(len(key_symbols)):
            key = key_symbols[i]
            # look up column corrdinate to determine number of spaces to pad
            row_index, column_index = self.KEY_COORDINATES[self.output_layout][conversion_map[i]]
            row_group = self.get_row_group(row_index)
            padded_key_symbols.append(key.ljust(self.column_max_widths[(row_group, column_index)]))
        return padded_key_symbols


    layer_keys_pointer = 0
    layer_keys = None
    def grab_next_n_columns(self, n_columns, input_layout, layer_keys = None, from_beginning = False):
        if layer_keys:
            self.layer_keys = layer_keys
        if from_beginning:
            self.layer_keys_pointer = 0

        begin = self.layer_keys_pointer
        end = begin + n_columns
        return self.layer_keys[self.layer_keys_pointer-n_keys:self.layer_keys_pointer]

    key_coordinates_counter = 0
    def get_padded_line(self, keys, key_from, key_to):
        (from_row, from_column) = self.KEY_COORDINATES[self.output_layout][self.key_coordinates_counter]
        row_group = self.get_row_group(from_row)
        self.key_coordinates_counter += key_to - key_from
        columns_of_keys = [cor[1] for cor in self.KEY_COORDINATES[self.output_layout] if cor[0] == from_row and cor[1] < from_column]
        # for rows with fewer columns that don't start with column 0, we need to insert leading spaces
        spaces = 0
        for c in range(from_column):
            if c in columns_of_keys:
                continue
            if (row_group,c) in self.column_max_widths:
                spaces += self.column_max_widths[(row_group,c)] + len(", ")
            else:
                spaces += 0
        leading_spaces = " " * spaces

        #print("|".join(keys[key_from:key_to]))
        return leading_spaces + ", ".join(keys[key_from:key_to]) + ","

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
            self.get_padded_line(keys,  0,  7),
            self.get_padded_line(keys,  7, 14),
            self.get_padded_line(keys, 14, 20),
            self.get_padded_line(keys, 20, 27),
            self.get_padded_line(keys, 27, 32),
            # left thumb
            self.get_padded_line(keys, 32, 34),
            self.get_padded_line(keys, 34, 35),
            self.get_padded_line(keys, 35, 38),
            # right hand
            self.get_padded_line(keys, 38, 45),
            self.get_padded_line(keys, 45, 52),
            self.get_padded_line(keys, 52, 58),
            self.get_padded_line(keys, 58, 65),
            self.get_padded_line(keys, 65, 70),
            # right thumb
            self.get_padded_line(keys, 70, 72),
            self.get_padded_line(keys, 72, 73),
            self.get_padded_line(keys, 73, 76),
            )
        elif self.output_layout == "LAYOUT_ergodox_pretty":
            formatted_key_symbols = """
{}   {}
{}   {}
{}   {}
{}   {}
{}   {}

{}   {}
{}   {}
{}   {}
""".format(
            self.get_padded_line(keys,  0,  7), self.get_padded_line(keys, 38, 45),
            self.get_padded_line(keys,  7, 14), self.get_padded_line(keys, 45, 52),
            self.get_padded_line(keys, 14, 20), self.get_padded_line(keys, 52, 58),
            self.get_padded_line(keys, 20, 27), self.get_padded_line(keys, 58, 65),
            self.get_padded_line(keys, 27, 32), self.get_padded_line(keys, 65, 70),

            self.get_padded_line(keys, 32, 34), self.get_padded_line(keys, 70, 72),
            self.get_padded_line(keys, 34, 35), self.get_padded_line(keys, 72, 73),
            self.get_padded_line(keys, 35, 38), self.get_padded_line(keys, 73, 76),

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

