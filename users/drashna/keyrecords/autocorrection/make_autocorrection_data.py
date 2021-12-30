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

"""Python program to make autocorrection_data.h.

This program reads "autocorrection_dict.txt" and generates a C source file
"autocorrection_data.h" with a serialized trie embedded as an array. Run this
program without arguments like

$ python3 make_autocorrection_data.py

Or to read from a different typo dict file, pass it as the first argument like

$ python3 make_autocorrection_data.py dict.txt

Each line of the dict file defines one typo and its correction with the syntax
"typo -> correction". Blank lines or lines starting with '#' are ignored.
Example:

  :thier        -> their
  fitler        -> filter
  lenght        -> length
  ouput         -> output
  widht         -> width

See autocorrection_dict_extra.txt for a larger example.

For full documentation, see
https://getreuer.info/posts/keyboards/autocorrection
"""

import sys
import textwrap
from typing import Any, Dict, List, Tuple

try:
  from english_words import english_words_lower_alpha_set as CORRECT_WORDS
except ImportError:
  print('Autocorrection will falsely trigger when a typo is a substring of a '
        'correctly spelled word. To check for this, install the english_words '
        'package and rerun this script:\n\n  pip install english_words\n')
  # Use a minimal word list as a fallback.
  CORRECT_WORDS = ('information', 'available', 'international', 'language',
                   'loosest', 'reference', 'wealthier', 'entertainment',
                   'association', 'provides', 'technology', 'statehood')

KC_A = 4
KC_SPC = 0x2c

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

  autocorrections = []
  typos = set()
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

      if typo in typos:
        print(f'Warning:{line_number}: Ignoring duplicate typo: "{typo}"')
        continue

      # Check that `typo` is valid.
      if not(all([ord('a') <= ord(c) <= ord('z') or c == ':' for c in typo])):
        print(f'Error:{line_number}: Typo "{typo}" has '
              'characters other than a-z and :.')
        sys.exit(1)
      for other_typo in typos:
        if typo in other_typo or other_typo in typo:
          print(f'Error:{line_number}: Typos may not be substrings of one '
                f'another, otherwise the longer typo would never trigger: '
                f'"{typo}" vs. "{other_typo}".')
          sys.exit(1)
      if len(typo) < 5:
        print(f'Warning:{line_number}: It is suggested that typos are at '
              f'least 5 characters long to avoid false triggers: "{typo}"')

      if typo.startswith(':') and typo.endswith(':'):
        if typo[1:-1] in CORRECT_WORDS:
          print(f'Warning:{line_number}: Typo "{typo}" is a correctly spelled '
                'dictionary word.')
      elif typo.startswith(':') and not typo.endswith(':'):
        for word in CORRECT_WORDS:
          if word.startswith(typo[1:]):
            print(f'Warning:{line_number}: Typo "{typo}" would falsely trigger '
                  f'on correctly spelled word "{word}".')
      elif not typo.startswith(':') and typo.endswith(':'):
        for word in CORRECT_WORDS:
          if word.endswith(typo[:-1]):
            print(f'Warning:{line_number}: Typo "{typo}" would falsely trigger '
                  f'on correctly spelled word "{word}".')
      elif not typo.startswith(':') and not typo.endswith(':'):
        for word in CORRECT_WORDS:
          if typo in word:
            print(f'Warning:{line_number}: Typo "{typo}" would falsely trigger '
                  f'on correctly spelled word "{word}".')

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


def serialize_trie(autocorrections: List[Tuple[str, str]],
                   trie: Dict[str, Any]) -> List[int]:
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
      data = [backspaces + 128] + list(bytes(correction, 'ascii')) + [0]

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

  def serialize(e):
    def kc_code(c):
      if ord('a') <= ord(c) <= ord('z'):
        return ord(c) - ord('a') + KC_A
      elif c == ':':
        return KC_SPC
      else:
        raise ValueError(f'Invalid character: {c}')

    encode_link = lambda link: [link['byte_offset'] & 255,
                                link['byte_offset'] >> 8]

    if not e['links']:  # Handle a leaf table entry.
      return e['data']
    elif len(e['links']) == 1:  # Handle a chain table entry.
      return list(map(kc_code, e['chars'])) + [0] #+ encode_link(e['links'][0]))
    else:  # Handle a branch table entry.
      data = []
      for c, link in zip(e['chars'], e['links']):
        data += [kc_code(c) | (0 if data else 64)] + encode_link(link)
      return data + [0]

  byte_offset = 0
  for e in table:  # To encode links, first compute byte offset of each entry.
    e['byte_offset'] = byte_offset
    byte_offset += len(serialize(e))
    assert 0 <= byte_offset <= 0xffff

  return [b for e in table for b in serialize(e)]  # Serialize final table.


def write_generated_code(autocorrections: List[Tuple[str, str]],
                         data: List[int],
                         file_name: str) -> None:
  """Writes autocorrection data as generated C code to `file_name`.

  Args:
    autocorrections: List of (typo, correction) tuples.
    data: List of ints in 0-255, the serialized trie.
    file_name: String, path of the output C file.
  """
  assert all(0 <= b <= 255 for b in data)
  typo_len = lambda e: len(e[0])
  min_typo = min(autocorrections, key=typo_len)[0]
  max_typo = max(autocorrections, key=typo_len)[0]
  generated_code = ''.join([
    '// Generated code.\n\n',
    f'// Autocorrection dictionary ({len(autocorrections)} entries):\n',
    ''.join(sorted(f'//   {typo:<{len(max_typo)}} -> {correction}\n'
                   for typo, correction in autocorrections)),
    f'\n#define AUTOCORRECTION_MIN_LENGTH {len(min_typo)}  // "{min_typo}"\n',
    f'#define AUTOCORRECTION_MAX_LENGTH {len(max_typo)}  // "{max_typo}"\n\n',
    textwrap.fill('static const uint8_t autocorrection_data[%d] PROGMEM = {%s};' % (
      len(data), ', '.join(map(str, data))), width=80, subsequent_indent='  '),
    '\n\n'])

  with open(file_name, 'wt') as f:
    f.write(generated_code)


def main(argv):
  dict_file = argv[1] if len(argv) > 1 else 'autocorrection_dict.txt'
  autocorrections = parse_file(dict_file)
  trie = make_trie(autocorrections)
  data = serialize_trie(autocorrections, trie)
  print(f'Processed %d autocorrection entries to table with %d bytes.'
        % (len(autocorrections), len(data)))
  write_generated_code(autocorrections, data, 'autocorrection_data.h')

if __name__ == '__main__':
  main(sys.argv)
