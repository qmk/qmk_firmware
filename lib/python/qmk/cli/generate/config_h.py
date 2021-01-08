"""Used by the make system to generate info_config.h from info.json.
"""
from milc import cli

from qmk.constants import LED_INDICATORS
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.info import info_json, rgblight_animations, rgblight_properties, rgblight_toggles
from qmk.path import is_keyboard, normpath

usb_prop_map = {
    'vid': 'VENDOR_ID',
    'pid': 'PRODUCT_ID',
    'device_ver': 'DEVICE_VER',
}


def debounce(debounce):
    """Return the config.h lines that set debounce
    """
    return """
#ifndef DEBOUNCE
#   define DEBOUNCE %s
#endif // DEBOUNCE
""" % debounce


def diode_direction(diode_direction):
    """Return the config.h lines that set diode direction
    """
    return """
#ifndef DIODE_DIRECTION
#   define DIODE_DIRECTION %s
#endif // DIODE_DIRECTION
""" % diode_direction


def keyboard_name(keyboard_name):
    """Return the config.h lines that set the keyboard's name.
    """
    return """
#ifndef DESCRIPTION
#    define DESCRIPTION %s
#endif // DESCRIPTION

#ifndef PRODUCT
#    define PRODUCT %s
#endif // PRODUCT
""" % (keyboard_name.replace("'", ""), keyboard_name.replace("'", ""))


def manufacturer(manufacturer):
    """Return the config.h lines that set the manufacturer.
    """
    return """
#ifndef MANUFACTURER
#    define MANUFACTURER %s
#endif // MANUFACTURER
""" % (manufacturer.replace("'", ""))


def direct_pins(direct_pins):
    """Return the config.h lines that set the direct pins.
    """
    rows = []

    for row in direct_pins:
        cols = ','.join(map(str, [col or 'NO_PIN' for col in row]))
        rows.append('{' + cols + '}')

    col_count = len(direct_pins[0])
    row_count = len(direct_pins)

    return """
#ifndef MATRIX_COLS
#    define MATRIX_COLS %s
#endif // MATRIX_COLS

#ifndef MATRIX_ROWS
#    define MATRIX_ROWS %s
#endif // MATRIX_ROWS

#ifndef DIRECT_PINS
#    define DIRECT_PINS {%s}
#endif // DIRECT_PINS
""" % (col_count, row_count, ','.join(rows))


def col_pins(col_pins):
    """Return the config.h lines that set the column pins.
    """
    cols = ','.join(map(str, [pin or 'NO_PIN' for pin in col_pins]))
    col_num = len(col_pins)

    return """
#ifndef MATRIX_COLS
#    define MATRIX_COLS %s
#endif // MATRIX_COLS

#ifndef MATRIX_COL_PINS
#    define MATRIX_COL_PINS {%s}
#endif // MATRIX_COL_PINS
""" % (col_num, cols)


def row_pins(row_pins):
    """Return the config.h lines that set the row pins.
    """
    rows = ','.join(map(str, [pin or 'NO_PIN' for pin in row_pins]))
    row_num = len(row_pins)

    return """
#ifndef MATRIX_ROWS
#    define MATRIX_ROWS %s
#endif // MATRIX_ROWS

#ifndef MATRIX_ROW_PINS
#    define MATRIX_ROW_PINS {%s}
#endif // MATRIX_ROW_PINS
""" % (row_num, rows)


def indicators(config):
    """Return the config.h lines that setup LED indicators.
    """
    defines = []

    for led, define in LED_INDICATORS.items():
        if led in config:
            defines.append('')
            defines.append('#ifndef %s' % (define,))
            defines.append('#   define %s %s' % (define, config[led]))
            defines.append('#endif // %s' % (define,))

    return '\n'.join(defines)


def layout_aliases(layout_aliases):
    """Return the config.h lines that setup layout aliases.
    """
    defines = []

    for alias, layout in layout_aliases.items():
        defines.append('')
        defines.append('#ifndef %s' % (alias,))
        defines.append('#   define %s %s' % (alias, layout))
        defines.append('#endif // %s' % (alias,))

    return '\n'.join(defines)


def matrix_pins(matrix_pins):
    """Add the matrix config to the config.h.
    """
    pins = []

    if 'direct' in matrix_pins:
        pins.append(direct_pins(matrix_pins['direct']))

    if 'cols' in matrix_pins:
        pins.append(col_pins(matrix_pins['cols']))

    if 'rows' in matrix_pins:
        pins.append(row_pins(matrix_pins['rows']))

    return '\n'.join(pins)


def rgblight(config):
    """Return the config.h lines that setup rgblight.
    """
    rgblight_config = []

    for json_key, config_key in rgblight_properties.items():
        if json_key in config:
            rgblight_config.append('')
            rgblight_config.append('#ifndef %s' % (config_key[0],))
            rgblight_config.append('#   define %s %s' % (config_key[0], config[json_key]))
            rgblight_config.append('#endif // %s' % (config_key[0],))

    for json_key, config_key in rgblight_toggles.items():
        if config.get(json_key):
            rgblight_config.append('')
            rgblight_config.append('#ifndef %s' % (config_key,))
            rgblight_config.append('#   define %s' % (config_key,))
            rgblight_config.append('#endif // %s' % (config_key,))

    for json_key, config_key in rgblight_animations.items():
        if 'animations' in config and config['animations'].get(json_key):
            rgblight_config.append('')
            rgblight_config.append('#ifndef %s' % (config_key,))
            rgblight_config.append('#   define %s' % (config_key,))
            rgblight_config.append('#endif // %s' % (config_key,))

    return '\n'.join(rgblight_config)


def usb_properties(usb_props):
    """Return the config.h lines that setup USB params.
    """
    usb_lines = []

    for info_name, config_name in usb_prop_map.items():
        if info_name in usb_props:
            usb_lines.append('')
            usb_lines.append('#ifndef ' + config_name)
            usb_lines.append('#    define %s %s' % (config_name, usb_props[info_name]))
            usb_lines.append('#endif // ' + config_name)

    return '\n'.join(usb_lines)


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('-kb', '--keyboard', help='Keyboard to generate config.h for.')
@cli.subcommand('Used by the make system to generate info_config.h from info.json', hidden=True)
@automagic_keyboard
@automagic_keymap
def generate_config_h(cli):
    """Generates the info_config.h file.
    """
    # Determine our keyboard(s)
    if not cli.config.generate_config_h.keyboard:
        cli.log.error('Missing paramater: --keyboard')
        cli.subcommands['info'].print_help()
        return False

    if not is_keyboard(cli.config.generate_config_h.keyboard):
        cli.log.error('Invalid keyboard: "%s"', cli.config.generate_config_h.keyboard)
        return False

    # Build the info.json file
    kb_info_json = info_json(cli.config.generate_config_h.keyboard)

    # Build the info_config.h file.
    config_h_lines = ['/* This file was generated by `qmk generate-config-h`. Do not edit or copy.' ' */', '', '#pragma once']

    if 'debounce' in kb_info_json:
        config_h_lines.append(debounce(kb_info_json['debounce']))

    if 'diode_direction' in kb_info_json:
        config_h_lines.append(diode_direction(kb_info_json['diode_direction']))

    if 'indicators' in kb_info_json:
        config_h_lines.append(indicators(kb_info_json['indicators']))

    if 'keyboard_name' in kb_info_json:
        config_h_lines.append(keyboard_name(kb_info_json['keyboard_name']))

    if 'layout_aliases' in kb_info_json:
        config_h_lines.append(layout_aliases(kb_info_json['layout_aliases']))

    if 'manufacturer' in kb_info_json:
        config_h_lines.append(manufacturer(kb_info_json['manufacturer']))

    if 'rgblight' in kb_info_json:
        config_h_lines.append(rgblight(kb_info_json['rgblight']))

    if 'matrix_pins' in kb_info_json:
        config_h_lines.append(matrix_pins(kb_info_json['matrix_pins']))

    if 'usb' in kb_info_json:
        config_h_lines.append(usb_properties(kb_info_json['usb']))

    # Show the results
    config_h = '\n'.join(config_h_lines)

    if cli.args.output:
        cli.args.output.parent.mkdir(parents=True, exist_ok=True)
        if cli.args.output.exists():
            cli.args.output.replace(cli.args.output.name + '.bak')
        cli.args.output.write_text(config_h)

        if not cli.args.quiet:
            cli.log.info('Wrote info_config.h to %s.', cli.args.output)

    else:
        print(config_h)
