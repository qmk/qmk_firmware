#!/usr/bin/env python

import argparse
import pycparser

def beautify_src_file(filename):
    src = {
        "before": [],
        "keys": [],
        "after": []
    }

    with open(filename) as f:
        current_section = "before"
        for line in f.read().split("\n"):
            if current_section == "before":
                if line == "const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {":
                    current_section = "keys"
                    src[current_section].append("const int keymaps[]={")
                else:
                    src[current_section].append(line)
            elif current_section == "keys":
                src[current_section].append(line)
                if line == "};":
                    current_section = "after"
            else:
                src[current_section].append(line)

    output = "\n".join(src["before"]) + "\n" 
    output += beautify_keys_section("\n".join(src["keys"])) + "\n"
    output += "\n".join(src["after"]) + "\n"
    return output

def beautify_keys_section(src):
    #parsed = pycparser.parse_file(c_filename)
    parsed = pycparser.CParser().parse(src)
    layer_output = []
    for layer in parsed.children()[0][1].init.exprs:
        ascii_key_symbols = transform_layer(layer)
        layer_output.append(pretty_output_layer(layer.name[0].value, ascii_key_symbols))
    return """
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{
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
{}

}};
    """.format(",\n\n".join(layer_output),)

def unpack_function(f):
    name = f.name.name
    args = []
    for arg in f.args.exprs:
        if type(arg) is pycparser.c_ast.Constant:
            args.append(arg.value)
        elif type(arg) is pycparser.c_ast.ID:
            args.append(arg.name)
    return "{}({})".format(name, ",".join(args))

def transform_raw_key_symbol(raw):
    if type(raw) is pycparser.c_ast.ID:
        if raw.name in ["KC_TRNS", "KC_TRANSPARENT"]:
            return "_______"
        return raw.name
    elif type(raw) is pycparser.c_ast.FuncCall:
        return unpack_function(raw)

def transform_layer(layer):
    transformed = [transform_raw_key_symbol(k) for k in layer.expr.args.exprs]
    return transformed

def pretty_output_layer(layer, keys):
    formatted_key_symbols = """
    // left hand
    {},
    {},
    {},
    {},
     {},

    // left thumb
    \t{},
    \t\t{},
    \t{},

    // right hand
    {},
    {},
    {},
    {},
     {},

    // right thumb
    {},
    {},
    {}
""".format(
        # left hand
        ", ".join(keys[0:7]),
        ", ".join(keys[7:14]),
        ", ".join(keys[14:20]),
        ", ".join(keys[20:27]),
        ", ".join(keys[27:32]),
        # left thumb
        ", ".join(keys[32:34]),
        keys[34],
        ", ".join(keys[35:38]),

        # right hand
        ", ".join(keys[38:45]),
        ", ".join(keys[45:52]),
        ", ".join(keys[52:58]),
        ", ".join(keys[58:65]),
        ", ".join(keys[65:70]),
        # right thumb
        ", ".join(keys[70:72]),
        keys[72],
        ", ".join(keys[73:76]),
    )

    s = "[{}] = LAYOUT_ergodox({})".format(layer, formatted_key_symbols)
    return s

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Beautify keymap.c downloaded from ErgoDox-Ez Configurator for easier customization.")

    parser.add_argument("-i", "--in-file", required=True, help="input file: c source code file that has the layer keymaps")
    parser.add_argument("-o", "--out-file", required=False, help="output file: beautified c filename. If not given, print it to STDOUT.")
    args = parser.parse_args()

    result = beautify_src_file(args.in_file)
    if args.out_file:
        with open(args.out_file, "w") as f:
            f.write(result)
    else:
        print(result)
