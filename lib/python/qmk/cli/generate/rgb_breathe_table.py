"""Generate rgblight_breathe_table.h
"""
import math
from argparse import ArgumentTypeError

from milc import cli

import qmk.path


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


@cli.argument('-c', '--center', arg_only=True, type=breathing_center, default=1.85, help='The breathing center value, from 1 to 2.7. Default: 1.85')
@cli.argument('-m', '--max', arg_only=True, type=breathing_max, default=255, help='The breathing maximum value, from 0 to 255. Default: 255')
@cli.argument('-o', '--output', arg_only=True, type=qmk.path.normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help='Quiet mode, only output error messages')
@cli.subcommand('Generates an RGB Light breathing table header.')
def generate_rgb_breathe_table(cli):
    """Generate a rgblight_breathe_table.h file containing a breathing LUT for RGB Lighting (Underglow) feature.
    """
    breathe_values = [0] * 256
    for pos in range(0, 256):
        breathe_values[pos] = (int)((math.exp(math.sin((pos/255) * math.pi)) - cli.args.center / math.e) * (cli.args.max / (math.e - 1 / math.e)))  # noqa: yapf insists there be no whitespace around /

    values_template = ''
    for s in range(0, 3):
        step = 1 << s

        values_template += '#if RGBLIGHT_BREATHE_TABLE_SIZE == {}\n'.format(256 >> s)

        for pos in range(0, 256, step):
            values_template += '    ' if pos % 8 == 0 else ''
            values_template += '0x{:02X}'.format(breathe_values[pos])
            values_template += ',' if (pos + step) < 256 else ''
            values_template += '\n' if (pos+step) % 8 == 0 else ' '  # noqa: yapf insists there be no whitespace around +

        values_template += '#endif'
        values_template += '\n\n' if s < 2 else ''

    table_template = '''#pragma once

#define RGBLIGHT_EFFECT_BREATHE_TABLE

// clang-format off

// Breathing center: {0:.2f}
// Breathing max:    {1:d}

const uint8_t PROGMEM rgblight_effect_breathe_table[] = {{
{2}
}};

static const int table_scale = 256 / sizeof(rgblight_effect_breathe_table);
'''.format(cli.args.center, cli.args.max, values_template)

    if cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        if cli.args.output.exists():
            cli.args.output.replace(cli.args.output.name + '.bak')
        cli.args.output.write_text(table_template)

        if not cli.args.quiet:
            cli.log.info('Wrote header to %s.', cli.args.output)
    else:
        print(table_template)
