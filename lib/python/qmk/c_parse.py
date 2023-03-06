"""Functions for working with config.h files.
"""
from pygments.lexers.c_cpp import CLexer
from pygments.token import Token
from pygments import lex
from itertools import islice
from pathlib import Path
import re

from milc import cli

from qmk.comment_remover import comment_remover

default_key_entry = {'x': -1, 'y': 0, 'w': 1}
single_comment_regex = re.compile(r'\s+/[/*].*$')
multi_comment_regex = re.compile(r'/\*(.|\n)*?\*/', re.MULTILINE)
layout_macro_define_regex = re.compile(r'^#\s*define')


def _get_chunks(it, size):
    """Break down a collection into smaller parts
    """
    it = iter(it)
    return iter(lambda: tuple(islice(it, size)), ())


def _preprocess_c_file(file):
    """Load file and strip comments
    """
    file_contents = file.read_text(encoding='utf-8')
    file_contents = comment_remover(file_contents)
    return file_contents.replace('\\\n', '')


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
    file_contents = _preprocess_c_file(file)

    for line in file_contents.split('\n'):
        if layout_macro_define_regex.match(line.lstrip()) and '(' in line and 'LAYOUT' in line:
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
                elif key['label'] not in matrix_locations:
                    cli.log.error('Invalid LAYOUT macro in %s: Key %s in macro %s has no matrix position!', file, key['label'], macro_name)
                elif len(matrix_locations.get(key['label'])) > 1:
                    cli.log.error('Invalid LAYOUT macro in %s: Key %s in macro %s has multiple matrix positions (%s)', file, key['label'], macro_name, ', '.join(str(x) for x in matrix_locations[key['label']]))
                else:
                    key['matrix'] = matrix_locations[key['label']][0]

            parsed_layouts[macro_name] = {
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
                if identifier not in matrix_locations:
                    matrix_locations[identifier] = []
                matrix_locations[identifier].append([row_num, col_num])

    return matrix_locations


def _coerce_led_token(_type, value):
    """ Convert token to valid info.json content
    """
    value_map = {
        'NO_LED': None,
        'LED_FLAG_ALL': 0xFF,
        'LED_FLAG_NONE': 0x00,
        'LED_FLAG_MODIFIER': 0x01,
        'LED_FLAG_UNDERGLOW': 0x02,
        'LED_FLAG_KEYLIGHT': 0x04,
        'LED_FLAG_INDICATOR': 0x08,
    }
    if _type is Token.Literal.Number.Integer:
        return int(value)
    if _type is Token.Literal.Number.Float:
        return float(value)
    if _type is Token.Literal.Number.Hex:
        return int(value, 0)
    if _type is Token.Name and value in value_map.keys():
        return value_map[value]


def _validate_led_config(matrix, matrix_rows, matrix_indexes, position, position_raw, flags):
    # TODO: Improve crude parsing/validation
    if len(matrix) != matrix_rows and len(matrix) != (matrix_rows / 2):
        raise ValueError("Unable to parse g_led_config matrix data")
    if len(position) != len(flags):
        raise ValueError(f"Number of g_led_config physical positions ({len(position)}) does not match number of flags ({len(flags)})")
    if len(matrix_indexes) and (max(matrix_indexes) >= len(flags)):
        raise ValueError(f"LED index {max(matrix_indexes)} is OOB in g_led_config - should be < {len(flags)}")
    if not all(isinstance(n, int) for n in matrix_indexes):
        raise ValueError("matrix indexes are not all ints")
    if (len(position_raw) % 2) != 0:
        raise ValueError("Malformed g_led_config position data")


def _parse_led_config(file, matrix_cols, matrix_rows):
    """Return any 'raw' led/rgb matrix config
    """
    matrix_raw = []
    position_raw = []
    flags = []

    found_led_config = False
    bracket_count = 0
    section = 0
    for _type, value in lex(_preprocess_c_file(file), CLexer()):
        # Assume g_led_config..stuff..;
        if value == 'g_led_config':
            found_led_config = True
        elif value == ';':
            found_led_config = False
        elif found_led_config:
            # Assume bracket count hints to section of config we are within
            if value == '{':
                bracket_count += 1
                if bracket_count == 2:
                    section += 1
            elif value == '}':
                bracket_count -= 1
            else:
                # Assume any non whitespace value here is important enough to stash
                if _type in [Token.Literal.Number.Integer, Token.Literal.Number.Float, Token.Literal.Number.Hex, Token.Name]:
                    if section == 1 and bracket_count == 3:
                        matrix_raw.append(_coerce_led_token(_type, value))
                    if section == 2 and bracket_count == 3:
                        position_raw.append(_coerce_led_token(_type, value))
                    if section == 3 and bracket_count == 2:
                        flags.append(_coerce_led_token(_type, value))
                elif _type in [Token.Comment.Preproc]:
                    # TODO: Promote to error
                    return None

    # Slightly better intrim format
    matrix = list(_get_chunks(matrix_raw, matrix_cols))
    position = list(_get_chunks(position_raw, 2))
    matrix_indexes = list(filter(lambda x: x is not None, matrix_raw))

    # If we have not found anything - bail with no error
    if not section:
        return None

    # Throw any validation errors
    _validate_led_config(matrix, matrix_rows, matrix_indexes, position, position_raw, flags)

    return (matrix, position, flags)


def find_led_config(file, matrix_cols, matrix_rows):
    """Search file for led/rgb matrix config
    """
    found = _parse_led_config(file, matrix_cols, matrix_rows)
    if not found:
        return None

    # Expand collected content
    (matrix, position, flags) = found

    # Align to output format
    led_config = []
    for index, item in enumerate(position, start=0):
        led_config.append({
            'x': item[0],
            'y': item[1],
            'flags': flags[index],
        })
    for r in range(len(matrix)):
        for c in range(len(matrix[r])):
            index = matrix[r][c]
            if index is not None:
                led_config[index]['matrix'] = [r, c]

    return led_config
