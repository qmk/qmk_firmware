"""Functions for working with config.h files.
"""
from pathlib import Path
import re

from milc import cli

from qmk.comment_remover import comment_remover

default_key_entry = {'x': -1, 'y': 0, 'w': 1}
single_comment_regex = re.compile(r' */[/*].*$')
multi_comment_regex = re.compile(r'/\*(.|\n)*?\*/', re.MULTILINE)


def strip_line_comment(string):
    """Removes comments from a single line string.
    """
    return single_comment_regex.sub('', string)


def strip_multiline_comment(string):
    """Removes comments from a single line string.
    """
    return multi_comment_regex.sub('', string)


def c_source_files(dir_names):
    """Returns a list of all *.c, *.h, and *.cpp files for a given list of directories

    Args:

        dir_names
            List of directories relative to `qmk_firmware`.
    """
    files = []
    for dir in dir_names:
        files.extend(file for file in Path(dir).glob('**/*') if file.suffix in ['.c', '.h', '.cpp'])
    return files


def find_layouts(file):
    """Returns list of parsed LAYOUT preprocessor macros found in the supplied include file.
    """
    file = Path(file)
    aliases = {}  # Populated with all `#define`s that aren't functions
    parsed_layouts = {}

    # Search the file for LAYOUT macros and aliases
    file_contents = file.read_text(encoding='utf-8')
    file_contents = comment_remover(file_contents)
    file_contents = file_contents.replace('\\\n', '')

    for line in file_contents.split('\n'):
        if line.startswith('#define') and '(' in line and 'LAYOUT' in line:
            # We've found a LAYOUT macro
            macro_name, layout, matrix = _parse_layout_macro(line.strip())

            # Reject bad macro names
            if macro_name.startswith('LAYOUT_kc') or not macro_name.startswith('LAYOUT'):
                continue

            # Parse the matrix data
            matrix_locations = _parse_matrix_locations(matrix, file, macro_name)

            # Parse the layout entries into a basic structure
            default_key_entry['x'] = -1  # Set to -1 so _default_key(key) will increment it to 0
            layout = layout.strip()
            parsed_layout = [_default_key(key) for key in layout.split(',')]

            for i, key in enumerate(parsed_layout):
                if 'label' not in key:
                    cli.log.error('Invalid LAYOUT macro in %s: Empty parameter name in macro %s at pos %s.', file, macro_name, i)
                elif key['label'] in matrix_locations:
                    key['matrix'] = matrix_locations[key['label']]

            parsed_layouts[macro_name] = {
                'key_count': len(parsed_layout),
                'layout': parsed_layout,
                'filename': str(file),
            }

        elif '#define' in line:
            # Attempt to extract a new layout alias
            try:
                _, pp_macro_name, pp_macro_text = line.strip().split(' ', 2)
                aliases[pp_macro_name] = pp_macro_text
            except ValueError:
                continue

    return parsed_layouts, aliases


def parse_config_h_file(config_h_file, config_h=None):
    """Extract defines from a config.h file.
    """
    if not config_h:
        config_h = {}

    config_h_file = Path(config_h_file)

    if config_h_file.exists():
        config_h_text = config_h_file.read_text(encoding='utf-8')
        config_h_text = config_h_text.replace('\\\n', '')
        config_h_text = strip_multiline_comment(config_h_text)

        for linenum, line in enumerate(config_h_text.split('\n')):
            line = strip_line_comment(line).strip()

            if not line:
                continue

            line = line.split()

            if line[0] == '#define':
                if len(line) == 1:
                    cli.log.error('%s: Incomplete #define! On or around line %s' % (config_h_file, linenum))
                elif len(line) == 2:
                    config_h[line[1]] = True
                else:
                    config_h[line[1]] = ' '.join(line[2:])

            elif line[0] == '#undef':
                if len(line) == 2:
                    if line[1] in config_h:
                        if config_h[line[1]] is True:
                            del config_h[line[1]]
                        else:
                            config_h[line[1]] = False
                else:
                    cli.log.error('%s: Incomplete #undef! On or around line %s' % (config_h_file, linenum))

    return config_h


def _default_key(label=None):
    """Increment x and return a copy of the default_key_entry.
    """
    default_key_entry['x'] += 1
    new_key = default_key_entry.copy()

    if label:
        new_key['label'] = label

    return new_key


def _parse_layout_macro(layout_macro):
    """Split the LAYOUT macro into its constituent parts
    """
    layout_macro = layout_macro.replace('\\', '').replace(' ', '').replace('\t', '').replace('#define', '')
    macro_name, layout = layout_macro.split('(', 1)
    layout, matrix = layout.split(')', 1)

    return macro_name, layout, matrix


def _parse_matrix_locations(matrix, file, macro_name):
    """Parse raw matrix data into a dictionary keyed by the LAYOUT identifier.
    """
    matrix_locations = {}

    for row_num, row in enumerate(matrix.split('},{')):
        if row.startswith('LAYOUT'):
            cli.log.error('%s: %s: Nested layout macro detected. Matrix data not available!', file, macro_name)
            break

        row = row.replace('{', '').replace('}', '')
        for col_num, identifier in enumerate(row.split(',')):
            if identifier != 'KC_NO':
                matrix_locations[identifier] = [row_num, col_num]

    return matrix_locations
