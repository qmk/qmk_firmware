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
"""Python program to make autocorrect_data.h.
This program reads from a prepared dictionary file and generates a C source file
"autocorrect_data.h" with a serialized trie embedded as an array. Run this
program and pass it as the first argument like:
$ qmk generate-autocorrect-data autocorrect_dict.txt
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

from milc import cli

import qmk.path
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.keymap import keymap_completer, locate_keymap

KC_A = 4
KC_SPC = 0x2c
KC_QUOT = 0x34

TYPO_CHARS = dict([
    ("'", KC_QUOT),
    (':', KC_SPC),  # "Word break" character.
] + [(chr(c), c + KC_A - ord('a')) for c in range(ord('a'),
                                                  ord('z') + 1)])  # Characters a-z.


def parse_file(file_name: str) -> List[Tuple[str, str]]:
    """Parses autocorrections dictionary file.
  Each line of the file defines one typo and its correction with the syntax
  "typo -> correction". Blank lines or lines starting with '#' are ignored. The
  function validates that typos only have characters a-z and that typos are not
  substrings of other typos, otherwise the longer typo would never trigger.
  Args:
    file_name: String, path of the autocorrections dictionary.
  Returns:
    List of (typo, correction) tuples.
  """

    try:
        from english_words import english_words_lower_alpha_set as correct_words
    except ImportError:
        cli.echo('Autocorrection will falsely trigger when a typo is a substring of a correctly spelled word.')
        cli.echo('To check for this, install the english_words package and rerun this script:')
        cli.echo('  {fg_cyan}python3 -m pip install english_words')
        # Use a minimal word list as a fallback.
        correct_words = ('information', 'available', 'international', 'language', 'loosest', 'reference', 'wealthier', 'entertainment', 'association', 'provides', 'technology', 'statehood')

    autocorrections = []
    typos = set()
    for line_number, typo, correction in parse_file_lines(file_name):
        if typo in typos:
            cli.log.warning('{fg_red}Error:%d:{fg_reset} Ignoring duplicate typo: "{fg_cyan}%s{fg_reset}"', line_number, typo)
            continue

        # Check that `typo` is valid.
        if not (all([c in TYPO_CHARS for c in typo])):
            cli.log.error('{fg_red}Error:%d:{fg_reset} Typo "{fg_cyan}%s{fg_reset}" has characters other than a-z, \' and :.', line_number, typo)
            sys.exit(1)
        for other_typo in typos:
            if typo in other_typo or other_typo in typo:
                cli.log.error('{fg_red}Error:%d:{fg_reset} Typos may not be substrings of one another, otherwise the longer typo would never trigger: "{fg_cyan}%s{fg_reset}" vs. "{fg_cyan}%s{fg_reset}".', line_number, typo, other_typo)
                sys.exit(1)
        if len(typo) < 5:
            cli.log.warning('{fg_yellow}Warning:%d:{fg_reset} It is suggested that typos are at least 5 characters long to avoid false triggers: "{fg_cyan}%s{fg_reset}"', line_number, typo)
        if len(typo) > 127:
            cli.log.error('{fg_red}Error:%d:{fg_reset} Typo exceeds 127 chars: "{fg_cyan}%s{fg_reset}"', line_number, typo)
            sys.exit(1)

        check_typo_against_dictionary(typo, line_number, correct_words)

        autocorrections.append((typo, correction))
        typos.add(typo)

    return autocorrections


def make_trie(autocorrections: List[Tuple[str, str]]) -> Dict[str, Any]:
    """Makes a trie from the the typos, writing in reverse.
  Args:
    autocorrections: List of (typo, correction) tuples.
  Returns:
    Dict of dict, representing the trie.
  """
    trie = {}
    for typo, correction in autocorrections:
        node = trie
        for letter in typo[::-1]:
            node = node.setdefault(letter, {})
        node['LEAF'] = (typo, correction)

    return trie


def parse_file_lines(file_name: str) -> Iterator[Tuple[int, str, str]]:
    """Parses lines read from `file_name` into typo-correction pairs."""

    line_number = 0
    for line in open(file_name, 'rt'):
        line_number += 1
        line = line.strip()
        if line and line[0] != '#':
            # Parse syntax "typo -> correction", using strip to ignore indenting.
            tokens = [token.strip() for token in line.split('->', 1)]
            if len(tokens) != 2 or not tokens[0]:
                print(f'Error:{line_number}: Invalid syntax: "{line}"')
                sys.exit(1)

            typo, correction = tokens
            typo = typo.lower()  # Force typos to lowercase.
            typo = typo.replace(' ', ':')

            yield line_number, typo, correction


def check_typo_against_dictionary(typo: str, line_number: int, correct_words) -> None:
    """Checks `typo` against English dictionary words."""

    if typo.startswith(':') and typo.endswith(':'):
        if typo[1:-1] in correct_words:
            cli.log.warning('{fg_yellow}Warning:%d:{fg_reset} Typo "{fg_cyan}%s{fg_reset}" is a correctly spelled dictionary word.', line_number, typo)
    elif typo.startswith(':') and not typo.endswith(':'):
        for word in correct_words:
            if word.startswith(typo[1:]):
                cli.log.warning('{fg_yellow}Warning:%d: {fg_reset}Typo "{fg_cyan}%s{fg_reset}" would falsely trigger on correctly spelled word "{fg_cyan}%s{fg_reset}".', line_number, typo, word)
    elif not typo.startswith(':') and typo.endswith(':'):
        for word in correct_words:
            if word.endswith(typo[:-1]):
                cli.log.warning('{fg_yellow}Warning:%d:{fg_reset} Typo "{fg_cyan}%s{fg_reset}" would falsely trigger on correctly spelled word "{fg_cyan}%s{fg_reset}".', line_number, typo, word)
    elif not typo.startswith(':') and not typo.endswith(':'):
        for word in correct_words:
            if typo in word:
                cli.log.warning('{fg_yellow}Warning:%d:{fg_reset} Typo "{fg_cyan}%s{fg_reset}" would falsely trigger on correctly spelled word "{fg_cyan}%s{fg_reset}".', line_number, typo, word)


def serialize_trie(autocorrections: List[Tuple[str, str]], trie: Dict[str, Any]) -> List[int]:
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
        if 'LEAF' in trie_node:  # Handle a leaf trie node.
            typo, correction = trie_node['LEAF']
            word_boundary_ending = typo[-1] == ':'
            typo = typo.strip(':')
            i = 0  # Make the autocorrection data for this entry and serialize it.
            while i < min(len(typo), len(correction)) and typo[i] == correction[i]:
                i += 1
            backspaces = len(typo) - i - 1 + word_boundary_ending
            assert 0 <= backspaces <= 63
            correction = correction[i:]
            bs_count = [backspaces + 128]
            data = bs_count + list(bytes(correction, 'ascii')) + [0]

            entry = {'data': data, 'links': [], 'byte_offset': 0}
            table.append(entry)
        elif len(trie_node) == 1:  # Handle trie node with a single child.
            c, trie_node = next(iter(trie_node.items()))
            entry = {'chars': c, 'byte_offset': 0}

            # It's common for a trie to have long chains of single-child nodes. We
            # find the whole chain so that we can serialize it more efficiently.
            while len(trie_node) == 1 and 'LEAF' not in trie_node:
                c, trie_node = next(iter(trie_node.items()))
                entry['chars'] += c

            table.append(entry)
            entry['links'] = [traverse(trie_node)]
        else:  # Handle trie node with multiple children.
            entry = {'chars': ''.join(sorted(trie_node.keys())), 'byte_offset': 0}
            table.append(entry)
            entry['links'] = [traverse(trie_node[c]) for c in entry['chars']]
        return entry

    traverse(trie)

    def serialize(e: Dict[str, Any]) -> List[int]:
        if not e['links']:  # Handle a leaf table entry.
            return e['data']
        elif len(e['links']) == 1:  # Handle a chain table entry.
            return [TYPO_CHARS[c] for c in e['chars']] + [0]  # + encode_link(e['links'][0]))
        else:  # Handle a branch table entry.
            data = []
            for c, link in zip(e['chars'], e['links']):
                data += [TYPO_CHARS[c] | (0 if data else 64)] + encode_link(link)
            return data + [0]

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
        cli.log.error('{fg_red}Error:{fg_reset} The autocorrection table is too large, a node link exceeds 64KB limit. Try reducing the autocorrection dict to fewer entries.')
        sys.exit(1)
    return [byte_offset & 255, byte_offset >> 8]


def write_generated_code(autocorrections: List[Tuple[str, str]], data: List[int], file_name: str) -> None:
    """Writes autocorrection data as generated C code to `file_name`.
  Args:
    autocorrections: List of (typo, correction) tuples.
    data: List of ints in 0-255, the serialized trie.
    file_name: String, path of the output C file.
  """
    assert all(0 <= b <= 255 for b in data)

    def typo_len(e: Tuple[str, str]) -> int:
        return len(e[0])

    min_typo = min(autocorrections, key=typo_len)[0]
    max_typo = max(autocorrections, key=typo_len)[0]
    generated_code = ''.join([
        '// Generated code.\n\n', f'// Autocorrection dictionary ({len(autocorrections)} entries):\n', ''.join(sorted(f'//   {typo:<{len(max_typo)}} -> {correction}\n' for typo, correction in autocorrections)),
        f'\n#define AUTOCORRECT_MIN_LENGTH {len(min_typo)}  // "{min_typo}"\n', f'#define AUTOCORRECT_MAX_LENGTH {len(max_typo)}  // "{max_typo}"\n\n', f'#define DICTIONARY_SIZE {len(data)}\n\n',
        textwrap.fill('static const uint8_t autocorrect_data[DICTIONARY_SIZE] PROGMEM = {%s};' % (', '.join(map(str, data))), width=120, subsequent_indent='    '), '\n\n'
    ])

    with open(file_name, 'wt') as f:
        f.write(generated_code)


@cli.argument('filename', default='autocorrect_dict.txt', help='The autocorrection database file')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.subcommand('Generate the autocorrection data file from a dictionary file.')
def generate_autocorrect_data(cli):
    autocorrections = parse_file(cli.args.filename)
    trie = make_trie(autocorrections)
    data = serialize_trie(autocorrections, trie)
    # Environment processing
    if cli.args.output == '-':
        cli.args.output = None

    if cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        cli.log.info('Creating autocorrect database at {fg_cyan}%s', cli.args.output)
        write_generated_code(autocorrections, data, cli.args.output)

    else:
        current_keyboard = cli.args.keyboard or cli.config.user.keyboard or cli.config.generate_autocorrect_data.keyboard
        current_keymap = cli.args.keymap or cli.config.user.keymap or cli.config.generate_autocorrect_data.keymap

        if current_keyboard and current_keymap:
            filename = locate_keymap(current_keyboard, current_keymap).parent / 'autocorrect_data.h'
            cli.log.info('Creating autocorrect database at {fg_cyan}%s', filename)
            write_generated_code(autocorrections, data, filename)

        else:
            write_generated_code(autocorrections, data, 'autocorrect_data.h')

    cli.log.info('Processed %d autocorrection entries to table with %d bytes.', len(autocorrections), len(data))
