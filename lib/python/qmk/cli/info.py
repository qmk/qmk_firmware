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


def show_keymap(kb_info_json, title_caps=True):
    """Render the keymap in ascii art.
    """
    keymap_path = locate_keymap(cli.config.info.keyboard, cli.config.info.keymap)

    if keymap_path and keymap_path.suffix == '.json':
        keymap_data = json.load(keymap_path.open(encoding='utf-8'))
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
    cli.echo('{fg_blue}Keyboard Folder{fg_reset}: %s', kb_info_json.get('keyboard_folder', 'Unknown'))
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
@cli.argument('-f', '--format', default='friendly', arg_only=True, help='Format to display the data in (friendly, text, json) (Default: friendly).')
@cli.argument('--ascii', action='store_true', default=not UNICODE_SUPPORT, help='Render layout box drawings in ASCII only.')
@cli.argument('-r', '--rules-mk', action='store_true', help='Render the parsed values of the keyboard\'s rules.mk file.')
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

    # Output in the requested format
    if cli.args.format == 'json':
        print(json.dumps(kb_info_json, cls=InfoJSONEncoder))
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

    if cli.config.info.keymap:
        show_keymap(kb_info_json, title_caps)
