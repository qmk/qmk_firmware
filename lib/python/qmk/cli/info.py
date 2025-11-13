"""Keyboard information script.

Compile an info.json for a particular keyboard and pretty-print it.
"""
import sys
import json

from milc import cli

from qmk.json_encoders import InfoJSONEncoder
from qmk.constants import COL_LETTERS, ROW_LETTERS
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.keyboard import keyboard_completer, keyboard_folder, render_layouts, render_layout, rules_mk
from qmk.info import info_json, keymap_json
from qmk.keymap import locate_keymap
from qmk.path import is_keyboard

UNICODE_SUPPORT = sys.stdout.encoding.lower().startswith('utf')


def _strip_api_content(info_json):
    # Ideally this would only be added in the API pathway.
    info_json.pop('platform', None)
    info_json.pop('platform_key', None)
    info_json.pop('processor_type', None)
    info_json.pop('protocol', None)
    info_json.pop('config_h_features', None)
    info_json.pop('keymaps', None)
    info_json.pop('keyboard_folder', None)
    info_json.pop('parse_errors', None)
    info_json.pop('parse_warnings', None)

    for layout in info_json.get('layouts', {}).values():
        layout.pop('filename', None)
        layout.pop('c_macro', None)
        layout.pop('json_layout', None)

    if 'matrix_pins' in info_json:
        info_json.pop('matrix_size', None)

    for feature in ['rgb_matrix', 'led_matrix']:
        if info_json.get(feature, {}).get("layout", None):
            info_json[feature].pop('led_count', None)

    return info_json


def show_keymap(kb_info_json, title_caps=True):
    """Render the keymap in ascii art.
    """
    keymap_path = locate_keymap(cli.config.info.keyboard, cli.config.info.keymap)

    if keymap_path and keymap_path.suffix == '.json':
        keymap_data = json.load(keymap_path.open(encoding='utf-8'))

        # cater for layout-less keymap.json
        if 'layout' not in keymap_data:
            return

        layout_name = keymap_data['layout']
        layout_name = kb_info_json.get('layout_aliases', {}).get(layout_name, layout_name)  # Resolve alias names

        for layer_num, layer in enumerate(keymap_data['layers']):
            if title_caps:
                cli.echo('{fg_cyan}Keymap %s Layer %s{fg_reset}:', cli.config.info.keymap, layer_num)
            else:
                cli.echo('{fg_cyan}keymap.%s.layer.%s{fg_reset}:', cli.config.info.keymap, layer_num)

            print(render_layout(kb_info_json['layouts'][layout_name]['layout'], cli.config.info.ascii, layer))


def show_layouts(kb_info_json, title_caps=True):
    """Render the layouts with info.json labels.
    """
    for layout_name, layout_art in render_layouts(kb_info_json, cli.config.info.ascii).items():
        title = f'Layout {layout_name.title()}' if title_caps else f'layouts.{layout_name}'
        cli.echo('{fg_cyan}%s{fg_reset}:', title)
        print(layout_art)  # Avoid passing dirty data to cli.echo()


def show_matrix(kb_info_json, title_caps=True):
    """Render the layout with matrix labels in ascii art.
    """
    for layout_name, layout in kb_info_json['layouts'].items():
        # Build our label list
        labels = []
        for key in layout['layout']:
            if 'matrix' in key:
                row = ROW_LETTERS[key['matrix'][0]]
                col = COL_LETTERS[key['matrix'][1]]

                labels.append(row + col)
            else:
                labels.append('')

        # Print the header
        if title_caps:
            cli.echo('{fg_blue}Matrix for "%s"{fg_reset}:', layout_name)
        else:
            cli.echo('{fg_blue}matrix_%s{fg_reset}:', layout_name)

        print(render_layout(kb_info_json['layouts'][layout_name]['layout'], cli.config.info.ascii, labels))


def show_leds(kb_info_json, title_caps=True):
    """Render LED indices per key, using the keyboard's key layout geometry.

    We build a map from (row, col) -> LED index using rgb_matrix/led_matrix layout,
    then label each key with its LED index. Keys without an associated LED are left blank.
    """
    # Prefer rgb_matrix, fall back to led_matrix
    led_feature = None
    for feature in ['rgb_matrix', 'led_matrix']:
        if 'layout' in kb_info_json.get(feature, {}):
            led_feature = feature
            break

    if not led_feature:
        cli.echo('{fg_yellow}No rgb_matrix/led_matrix layout found to derive LED indices.{fg_reset}')
        return

    # Build mapping from matrix position -> LED indices for faster lookup later
    by_matrix = {}
    for idx, led in enumerate(kb_info_json[led_feature]['layout']):
        if 'matrix' in led:
            led_key = tuple(led.get('matrix'))
            by_matrix[led_key] = idx

    # For each keyboard layout (e.g., LAYOUT), render keys labeled with LED index (or blank)
    for layout_name, layout in kb_info_json['layouts'].items():
        labels = []
        for key in layout['layout']:
            led_key = tuple(key.get('matrix'))
            label = str(by_matrix[led_key]) if led_key in by_matrix else ''

            labels.append(label)

        # Header
        if title_caps:
            cli.echo('{fg_blue}LED indices for "%s"{fg_reset}:', layout_name)
        else:
            cli.echo('{fg_blue}leds_%s{fg_reset}:', layout_name)

        print(render_layout(kb_info_json['layouts'][layout_name]['layout'], cli.config.info.ascii, labels))


def print_friendly_output(kb_info_json):
    """Print the info.json in a friendly text format.
    """
    cli.echo('{fg_blue}Keyboard Name{fg_reset}: %s', kb_info_json.get('keyboard_name', 'Unknown'))
    cli.echo('{fg_blue}Manufacturer{fg_reset}: %s', kb_info_json.get('manufacturer', 'Unknown'))
    if 'url' in kb_info_json:
        cli.echo('{fg_blue}Website{fg_reset}: %s', kb_info_json.get('url', ''))
    if kb_info_json.get('maintainer', 'qmk') == 'qmk':
        cli.echo('{fg_blue}Maintainer{fg_reset}: QMK Community')
    else:
        cli.echo('{fg_blue}Maintainer{fg_reset}: %s', kb_info_json['maintainer'])
    cli.echo('{fg_blue}Layouts{fg_reset}: %s', ', '.join(sorted(kb_info_json['layouts'].keys())))
    cli.echo('{fg_blue}Processor{fg_reset}: %s', kb_info_json.get('processor', 'Unknown'))
    cli.echo('{fg_blue}Bootloader{fg_reset}: %s', kb_info_json.get('bootloader', 'Unknown'))
    if 'layout_aliases' in kb_info_json:
        aliases = [f'{key}={value}' for key, value in kb_info_json['layout_aliases'].items()]
        cli.echo('{fg_blue}Layout aliases:{fg_reset} %s' % (', '.join(aliases),))


def print_text_output(kb_info_json):
    """Print the info.json in a plain text format.
    """
    for key in sorted(kb_info_json):
        if key == 'layouts':
            cli.echo('{fg_blue}layouts{fg_reset}: %s', ', '.join(sorted(kb_info_json['layouts'].keys())))
        else:
            cli.echo('{fg_blue}%s{fg_reset}: %s', key, kb_info_json[key])

    if cli.config.info.layouts:
        show_layouts(kb_info_json, False)

    if cli.config.info.matrix:
        show_matrix(kb_info_json, False)

    if cli.config_source.info.keymap and cli.config_source.info.keymap != 'config_file':
        show_keymap(kb_info_json, False)


def print_dotted_output(kb_info_json, prefix=''):
    """Print the info.json in a plain text format with dot-joined keys.
    """
    for key in sorted(kb_info_json):
        new_prefix = f'{prefix}.{key}' if prefix else key

        if key in ['parse_errors', 'parse_warnings']:
            continue
        elif key == 'layouts' and prefix == '':
            cli.echo('{fg_blue}layouts{fg_reset}: %s', ', '.join(sorted(kb_info_json['layouts'].keys())))
        elif isinstance(kb_info_json[key], dict):
            print_dotted_output(kb_info_json[key], new_prefix)
        elif isinstance(kb_info_json[key], list):
            cli.echo('{fg_blue}%s{fg_reset}: %s', new_prefix, ', '.join(map(str, sorted(kb_info_json[key]))))
        else:
            cli.echo('{fg_blue}%s{fg_reset}: %s', new_prefix, kb_info_json[key])


def print_parsed_rules_mk(keyboard_name):
    rules = rules_mk(keyboard_name)
    for k in sorted(rules.keys()):
        print('%s = %s' % (k, rules[k]))
    return


@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='Keyboard to show info for.')
@cli.argument('-km', '--keymap', help='Keymap to show info for (Optional).')
@cli.argument('-l', '--layouts', action='store_true', help='Render the layouts.')
@cli.argument('-m', '--matrix', action='store_true', help='Render the layouts with matrix information.')
@cli.argument('-L', '--leds', action='store_true', help='Render the LED layout with LED indices (rgb_matrix/led_matrix).')
@cli.argument('-f', '--format', default='friendly', arg_only=True, help='Format to display the data in (friendly, text, json) (Default: friendly).')
@cli.argument('--ascii', action='store_true', default=not UNICODE_SUPPORT, help='Render layout box drawings in ASCII only.')
@cli.argument('-r', '--rules-mk', action='store_true', help='Render the parsed values of the keyboard\'s rules.mk file.')
@cli.argument('-a', '--api', action='store_true', help='Show fully processed info intended for API consumption.')
@cli.subcommand('Keyboard information.')
@automagic_keyboard
@automagic_keymap
def info(cli):
    """Compile an info.json for a particular keyboard and pretty-print it.
    """
    # Determine our keyboard(s)
    if not cli.config.info.keyboard:
        cli.log.error('Missing parameter: --keyboard')
        cli.subcommands['info'].print_help()
        return False

    if not is_keyboard(cli.config.info.keyboard):
        cli.log.error('Invalid keyboard: "%s"', cli.config.info.keyboard)
        return False

    if bool(cli.args.rules_mk):
        print_parsed_rules_mk(cli.config.info.keyboard)
        return False

    # default keymap stored in config file should be ignored
    if cli.config_source.info.keymap == 'config_file':
        cli.config_source.info.keymap = None

    # Build the info.json file
    if cli.config.info.keymap:
        kb_info_json = keymap_json(cli.config.info.keyboard, cli.config.info.keymap)
    else:
        kb_info_json = info_json(cli.config.info.keyboard)

    if not cli.args.api:
        kb_info_json = _strip_api_content(kb_info_json)

    # Output in the requested format
    if cli.args.format == 'json':
        print(json.dumps(kb_info_json, cls=InfoJSONEncoder, sort_keys=True))
        return True
    elif cli.args.format == 'text':
        print_dotted_output(kb_info_json)
        title_caps = False
    elif cli.args.format == 'friendly':
        print_friendly_output(kb_info_json)
        title_caps = True
    else:
        cli.log.error('Unknown format: %s', cli.args.format)
        return False

    # Output requested extras
    if cli.config.info.layouts:
        show_layouts(kb_info_json, title_caps)

    if cli.config.info.matrix:
        show_matrix(kb_info_json, title_caps)

    if cli.config.info.leds:
        show_leds(kb_info_json, title_caps)

    if cli.config.info.keymap:
        show_keymap(kb_info_json, title_caps)
