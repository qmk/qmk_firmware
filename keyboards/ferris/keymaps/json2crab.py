#!/usr/bin/env python3

import argparse
import sys
import json

indent_level=4

def parse_cli():
    parser = argparse.ArgumentParser(description='Ferris keymap formatter')
    parser.add_argument("--input", type=argparse.FileType('r'),
        default=sys.stdin, help="Input keymap (json file produced by qmk configurator)")
    return parser.parse_args()

def col_index(key_index):
    if key_index < 30:
        col = key_index % 5
    else:
        col = key_index % 2
    return col

def format_layers(layers):
    formatted = indent_level * " " + "\"layers\": [\n"
    max_key_length = {}
    for layer in layers:
        for (index, keycode) in enumerate(layer):
            col = col_index(index)
            max_length = max_key_length.get(col)
            if (not max_length) or len(keycode) > max_length:
                max_key_length.update({col: len(keycode)})
    for (layer_index, layer) in enumerate(layers):
        formatted += 2 * indent_level * " "
        formatted += "["
        for (index, keycode) in enumerate(layer):
            if index > 30 and index % 2 == 0 or index % 5 == 0 and index != 0:
                formatted += (1 + 2 * indent_level) * " "
            formatted += json.dumps(keycode)
            if index == 33:
                formatted += "\n"
            elif index > 30 and index % 2 == 1 or index % 5 == 4:
                formatted += ",\n"
            else:
                n_spaces = max_key_length[col_index(index)] - len(keycode)
                formatted += n_spaces * " "
                formatted += ", "
            if index % 10 == 9:
                formatted += "\n"
        formatted += 2 * indent_level * " "
        if layer_index < len(layers) - 1:
            formatted += "],\n"
        else:
            formatted += "]\n"
    formatted += indent_level * " "
    formatted += "]"

    return formatted

def format_keymap(keymap_json):
    formatted = "{"
    for (index, k) in enumerate(keymap_json):
        if k == "layers":
            formatted += format_layers(keymap_json[k])
        else:
            formatted += f"{indent_level * ' '}{json.dumps(k)}: {json.dumps(keymap_json[k])}"
        if index < len(keymap_json) - 1:
            formatted += ","
        formatted += "\n"
    formatted += "}"
    return formatted

def main():
    args=parse_cli()
    keymap_json = json.loads(args.input.read())
    print(format_keymap(keymap_json))

main()
