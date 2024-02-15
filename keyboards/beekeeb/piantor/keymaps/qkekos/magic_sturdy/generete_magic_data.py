# Copyright 2021 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""Python program to make magic_data.h.
This program reads from a prepared dictionary file and generates a C source file
"magic_data.h" with a serialized trie embedded as an array. Run this
program and pass it as the first argument like:
$ qmk generate-magic-data magic_dict.txt
Each line of the dict file defines one typo and its correction with the syntax
"typo -> correction". Blank lines or lines starting with '#' are ignored.
Example:
  :thier        -> their
  fitler        -> filter
  lenght        -> length
  ouput         -> output
  widht         -> width
For full documentation, see QMK Docs
"""

import sys
import textwrap
from typing import Any, Dict, Iterator, List, Tuple
from pathlib import Path

SEPARATORS = {
    "☆": "magic",
    "ᐉ": "repeat",
    "★": "db_magic",
}

THIS_FOLDER = Path(__file__).parent

IN_FILE = THIS_FOLDER / "magic.txt"
OUT_FILE = THIS_FOLDER / 'magic_data.h'

tokens_list = list[tuple[str, str]]
tokens_dict = dict[str, tokens_list]

max_global_typo_len = 0

KC_A = 4
KC_SPC = 0x2c
KC_DOT = 55
KC_QUOT = 0x34

TYPO_CHARS = dict([
    ("'", KC_QUOT),
    (".", KC_DOT),
    ('→', KC_SPC),  # "Word break" character.
] + [(chr(c), c + KC_A - ord('a')) for c in range(ord('a'), ord('z') + 1)])
#   Characters a-z.


def make_trie(magicions: tokens_list) -> Dict[str, Any]:
    trie = {}

    for typo, correction in magicions:
        node = trie
        for letter in typo[::-1]:
            node = node.setdefault(letter, {})
        node['MATCH'] = (typo, correction)

    return trie


def serialize_trie(trie: Dict[str, Any]) -> List[int]:
    """Serializes trie and correction data in a form readable by the C code.
  Args:
    autocorrections: List of (typo, correction) tuples.
    trie: Dict of dicts.
  Returns:
    List of ints in the range 0-255.
  """
    table = []

    # Traverse trie in depth first order.
    def traverse(trie_node):
        if 'MATCH' in trie_node:  # Handle a MATCH trie node.
            typo, correction = trie_node['MATCH']
            word_boundary_ending = typo[-1] == '→'
            typo = typo.strip('→')
            i = 0  # Make the autocorrection data for this entry and serialize it.
            while i < min(len(typo), len(correction)) and typo[i] == correction[i]:
                i += 1
            backspaces = len(typo) - i + word_boundary_ending

            if not typo:
                backspaces = 0

            assert 0 <= backspaces <= 63
            correction = correction[i:]
            bs_count = [backspaces + 128 + (64 if len(trie_node) > 1 else 0)]

            data = bs_count + list(bytes(correction, 'ascii')) + [0]
            del trie_node['MATCH']
        else:
            data = []

        if len(trie_node) == 0:
            entry = {'data': data, 'links': [], 'byte_offset': 0}
            table.append(entry)
        elif len(trie_node) == 1:  # Handle trie node with a single child.
            c, trie_node = next(iter(trie_node.items()))
            entry = {'data': data, 'chars': c, 'byte_offset': 0}

            # It's common for a trie to have long chains of single-child nodes. We
            # find the whole chain so that we can serialize it more efficiently.
            while len(trie_node) == 1 and 'MATCH' not in trie_node:
                c, trie_node = next(iter(trie_node.items()))
                entry['chars'] += c

            table.append(entry)
            entry['links'] = [traverse(trie_node)]
        else:  # Handle trie node with multiple children.
            entry = {'data': data, 'chars': ''.join(sorted(trie_node.keys())), 'byte_offset': 0}
            table.append(entry)
            entry['links'] = [traverse(trie_node[c]) for c in entry['chars']]

        return entry

    traverse(trie)

    def serialize(e: Dict[str, Any]) -> List[int]:
        data = e['data']
        if not e['links']:  # Handle a leaf table entry.
            return data
        elif len(e['links']) == 1:  # Handle a chain table entry.
            return data + [TYPO_CHARS[c] for c in e['chars']] + [0]  # + encode_link(e['links'][0]))
        else:  # Handle a branch table entry.
            links = []
            for c, link in zip(e['chars'], e['links']):
                links += [TYPO_CHARS[c] | (0 if links else 64)] + encode_link(link)
            return data + links + [0]

    byte_offset = 0
    for e in table:  # To encode links, first compute byte offset of each entry.
        e['byte_offset'] = byte_offset
        byte_offset += len(serialize(e))
        assert 0 <= byte_offset <= 0xffff

    return [b for e in table for b in serialize(e)]  # Serialize final table.


def encode_link(link: Dict[str, Any]) -> List[int]:
    """Encodes a node link as two bytes."""
    byte_offset = link['byte_offset']
    if not (0 <= byte_offset <= 0xffff):
        sys.exit(1)
    return [byte_offset & 255, byte_offset >> 8]


def typo_len(e: Tuple[str, str]) -> int:
    return len(e[0])


def to_hex(b: int) -> str:
    return f'0x{b:02X}'


def get_line_tokens(line: str, sep: str = "->") -> tuple[str, str]:
    if line.startswith("#") or line.startswith("\\") or not line:
        raise ValueError(f"Invalid line {line}")

    tokens = [token.strip() for token in line.split(sep, 1)]

    if len(tokens) != 2 or not tokens[0]:
        raise ValueError(f"Invalid line {line}")

    tokens[0] = tokens[0].lower().replace(' ', '→')
    return tokens[0], tokens[1]


def handle_same_double_separator(
        context: str, complement: str,
        tokens: tokens_dict, line: str
) -> None:
    separator = context[-1]

    for tmp_context, tmp_complement in tokens[separator]:
        if tmp_context != context[:-2]:
            continue

        tokens[separator].append((tmp_complement, complement))
        break

    else:
        raise ValueError(f"No single tap case for line {line}")


def handle_different_double_separator(
        context: str, complement: str,
        tokens: tokens_dict, line: str
) -> None:
    outer_separator = context[-1]
    inner_separator = context[-2]

    for tmp_context, tmp_complement in tokens[inner_separator]:
        if tmp_context != context[:-2]:
            continue

        tokens[outer_separator].append((tmp_complement, complement))
        break

    else:
        raise ValueError(f"No single tap case for line {line}")


def parse_lines(filename: str) -> tokens_dict:
    with open(filename, "r", encoding="utf-8") as file:
        lines = [line.strip() for line in file.readlines()]

    separator_to_tokens = {separator: [] for separator in SEPARATORS}

    for line in lines:
        try:
            context, complement = get_line_tokens(line)
        except ValueError:
            continue

        for separator in SEPARATORS:
            if not context.endswith(separator):
                continue

            sep_count = sum(
                context.count(separator) for separator in SEPARATORS
            )

            if sep_count == 1:
                context = context.replace(separator, "")
                separator_to_tokens[separator].append((context, complement))
                break

            if context[-2] == separator:
                handle_same_double_separator(
                    context, complement,
                    separator_to_tokens, line
                )

                break

            handle_different_double_separator(
                context, complement,
                separator_to_tokens, line
            )

    return separator_to_tokens


def generate_magic_data_core(tokens: tokens_list, type_name: str) -> List[str]:
    type_name = type_name.upper()

    trie = make_trie(tokens)
    data = serialize_trie(trie)

    assert all(0 <= b <= 255 for b in data)

    min_typo = min(tokens, key=typo_len)[0]
    max_typo = max(tokens, key=typo_len)[0]

    global max_global_typo_len
    max_global_typo_len = max(max_global_typo_len, len(max_typo))

    magic_data_h_lines = [
        f'// {"-" * 50}\n',
        f'// {type_name.title()} dictionary ({len(tokens)} entries):'
    ]

    for typo, correction in tokens:
        magic_data_h_lines.append(f'//   {typo:<{len(max_typo)}} -> {correction}')

    magic_data_h_lines.append('')
    magic_data_h_lines.append(f'#define {type_name}_MIN_LENGTH {len(min_typo)} // "{min_typo}"')
    magic_data_h_lines.append(f'#define {type_name}_MAX_LENGTH {len(max_typo)} // "{max_typo}"')
    magic_data_h_lines.append(f'#define {type_name}_DICTIONARY_SIZE {len(data)}')
    magic_data_h_lines.append('')
    magic_data_h_lines.append(f'static const uint8_t {type_name.lower()}_data[{type_name}_DICTIONARY_SIZE] PROGMEM = ' + "{")
    magic_data_h_lines.append(textwrap.fill('    %s' % (', '.join(map(to_hex, data))), width=100, subsequent_indent='    '))
    magic_data_h_lines.append('};\n')

    return magic_data_h_lines


def generate_magic_data():
    magic_data_h_lines = ['#pragma once', '']
    trie_lines = []

    for separator, tokens in parse_lines(IN_FILE).items():
        trie_lines.extend(
            generate_magic_data_core(tokens, SEPARATORS.get(separator))
        )

    magic_data_h_lines.extend([f"#define MAX_CONTEXT_LENGTH {max_global_typo_len + 1}", ""])
    magic_data_h_lines.extend(trie_lines)

    with open(OUT_FILE, "r", encoding="utf-8") as file:
        if file.read() == "\n".join(magic_data_h_lines):
            return

    # Show the results
    with open(OUT_FILE, "w", encoding="utf-8") as file:
        file.write("\n".join(magic_data_h_lines))


# todo make it run only if date_modified of .txt is < date_modified of .h

if __name__ == '__main__':
    generate_magic_data()
