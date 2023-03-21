"""Generate rgblight_breathe_table.h
"""
import math
from argparse import ArgumentTypeError

from milc import cli

from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE
from qmk.commands import dump_lines
from qmk.path import normpath


def breathing_center(value):
    value = float(value)
    if value >= 1 and value <= 2.7:
        return value
    else:
        raise ArgumentTypeError('Breathing center must be between 1 and 2.7')


def breathing_max(value):
    value = int(value)
    if value in range(0, 256):
        return value
    else:
        raise ArgumentTypeError('Breathing max must be between 0 and 255')


def _generate_table(lines, center, maximum):
    breathe_values = [0] * 256
    for pos in range(0, 256):
        breathe_values[pos] = (int)((math.exp(math.sin((pos / 255) * math.pi)) - center / math.e) * (maximum / (math.e - 1 / math.e)))

    values_template = ''
    for s in range(0, 3):
        step = 1 << s

        values_template += '#if RGBLIGHT_BREATHE_TABLE_SIZE == {}\n'.format(256 >> s)

        for pos in range(0, 256, step):
            values_template += '    ' if pos % 8 == 0 else ''
            values_template += '0x{:02X}'.format(breathe_values[pos])
            values_template += ',' if (pos + step) < 256 else ''
            values_template += '\n' if (pos + step) % 8 == 0 else ' '

        values_template += '#endif'
        values_template += '\n\n' if s < 2 else ''

    table_template = '''#define RGBLIGHT_EFFECT_BREATHE_TABLE

// Breathing center: {0:.2f}
// Breathing max:    {1:d}

const uint8_t PROGMEM rgblight_effect_breathe_table[] = {{
{2}
}};

static const int table_scale = 256 / sizeof(rgblight_effect_breathe_table);
'''.format(center, maximum, values_template)
    lines.append(table_template)


@cli.argument('-c', '--center', arg_only=True, type=breathing_center, default=1.85, help='The breathing center value, from 1 to 2.7. Default: 1.85')
@cli.argument('-m', '--max', arg_only=True, type=breathing_max, default=255, help='The breathing maximum value, from 0 to 255. Default: 255')
@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help='Quiet mode, only output error messages')
@cli.subcommand('Generates an RGB Light breathing table header.')
def generate_rgb_breathe_table(cli):
    """Generate a rgblight_breathe_table.h file containing a breathing LUT for RGB Lighting (Underglow) feature.
    """

    # Build the header file.
    header_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once', '// clang-format off']

    _generate_table(header_lines, cli.args.center, cli.args.max)

    # Show the results
    dump_lines(cli.args.output, header_lines, cli.args.quiet)
