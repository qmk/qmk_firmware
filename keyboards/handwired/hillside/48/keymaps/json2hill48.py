#!/usr/bin/env python3

# Copyright 2020-2022 Pierre Viseu Chevalier, Michael McCoyd (@pierrechevalier83, @mmccoyd)
# SPDX-License-Identifier: GPL-2.0-or-later

"""Pretty print keymap json in more readable row/side organized format, based on ROW_SIZES."""

import argparse
import json
import sys
from typing import NamedTuple

"""Print keymap json in row and side format, though as still re-readable json.

For example, for one layer:

 ["KC_TAB" , "KC_Q"   , "KC_W"   , "KC_E"   , "KC_R"   , "KC_T",
  "KC_Y"   , "KC_U"   , "KC_I"   , "KC_O"   , "KC_P"   , "KC_BSPC",

  "KC_LCTL", "KC_A"   , "KC_S"   , "KC_D"   , "KC_F"   , "KC_G",
  "KC_H"   , "KC_J"   , "KC_K"   , "KC_L"   , "KC_SCLN", "KC_QUOT",

  "KC_LSFT", "KC_Z"   , "KC_X"   , "KC_C"   , "KC_V"   , "KC_B"   , "KC_GRV",
  "KC_ESC" , "KC_N"   , "KC_M"   , "KC_COMM", "KC_DOT" , "KC_SLSH", "KC_RSFT",

  "KC_ENT" , "KC_LGUI", "KC_LALT", "MO(5)"  , "MO(3)",
  "MO(4)"  , "KC_SPC" , "KC_LALT", "KC_RGUI", "KC_APP"
 ],
"""

# The structure of the keymap. Tuples describing row sizes.
# (<Keys upto and including (one-indexed) keycount x> <are in half rows of y>)
ROW_SIZES = [(24, 6),
             (38, 7),
             (48, 5),
             ]

###
### Below here should not need to changed for different keyboards
###

LAST_KEY = ROW_SIZES[-1][0] - 1

indent_level=4 # number of spaces of initial indent per output line

def parse_cli():
    parser = argparse.ArgumentParser(description='Hillside keymap formatter')
    parser.add_argument("--input", type=argparse.FileType('r'),
        default=sys.stdin, help="Input keymap "
                        "(json file produced by qmk configurator)")
    return parser.parse_args()

class Column(NamedTuple):
    """Column number within keymap side, if it ends side, and ends row.

    Position within a keyboard row runs from 0 to n and again 0 to n"""
    num: int
    ends_side: bool
    ends_row: bool

def get_col(key_index):
    """Return Column for key_index."""
    index_prior = 0 # index of last key in rows of the prior size
    for keys_upto, num_cols in ROW_SIZES: # For row sizes from top
        if key_index < keys_upto: # Find range key_index is in
            col_num = (key_index - index_prior) % num_cols
            return Column(col_num, # Return column plus side and row ends flags
                          ends_side=col_num == num_cols - 1,
                          ends_row=(keys_upto - 1 - key_index) %
                          (2 * num_cols) == 0)
        index_prior = keys_upto # Big O: row ranges * keys, but range is small

def format_layers(layers):
    formatted = indent_level * " " + "\"layers\": [\n"

    # Find max key length per column
    max_key_length = {}
    for layer in layers:
        for (index, keycode) in enumerate(layer):
            col = get_col(index)
            max_length = max_key_length.get(col.num)
            if (not max_length) or len(keycode) > max_length:
                max_key_length.update({col.num: len(keycode)})
    # Format each layer
    for (layer_index, layer) in enumerate(layers):
        # Opening [
        formatted += 2 * indent_level * " "
        formatted += "["

        # Split keys into pairs of left and right rows by key row length
        for (index, keycode) in enumerate(layer):
            col = get_col(index)

            # Indent for rows past first
            if col.num == 0 and index != 0:
                formatted += (1 + 2 * indent_level) * " "

            # Print key
            formatted += json.dumps(keycode)

            # End layer, or end side, or space to next key
            if index == LAST_KEY:
                formatted += "\n"
            elif col.ends_side:
                formatted += ",\n"
            else:
                n_spaces = max_key_length[get_col(index).num] - len(keycode)
                formatted += n_spaces * " "
                formatted += ", "

            # Split groups of row sides
            if col.ends_row:
                formatted += "\n"

        # Closing ] with , or without
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

if __name__ == "__main__":
    main()
