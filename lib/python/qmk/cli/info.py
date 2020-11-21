"""Keyboard information script.

Compile an info.json for a particular keyboard and pretty-print it.
"""
import json
import platform

from milc import cli

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.keyboard import render_layouts, render_layout
from qmk.keymap import locate_keymap
from qmk.info import info_json
from qmk.path import is_keyboard

platform_id = platform.platform().lower()

ROW_LETTERS = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnop'
COL_LETTERS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijilmnopqrstuvwxyz'


def show_keymap(kb_info_json, title_caps=True):
    """Render the keymap in ascii art.
    """
    keymap_path = locate_keymap(cli.config.info.keyboard, cli.config.info.keymap)

    if keymap_path and keymap_path.suffix == '.json':
        if title_caps:
            cli.echo('{fg_blue}Keymap "%s"{fg_reset}:', cli.config.info.keymap)
        else:
            cli.echo('{fg_blue}keymap_%s{fg_reset}:', cli.config.info.keymap)

        keymap_data = json.load(keymap_path.open())
        layout_name = keymap_data['layout']

        for layer_num, layer in enumerate(keymap_data['layers']):
            if title_caps:
                cli.echo('{fg_cyan}Layer %s{fg_reset}:', layer_num)
            else:
                cli.echo('{fg_cyan}layer_%s{fg_reset}:', layer_num)

            print(render_layout(kb_info_json['layouts'][layout_name]['layout'], cli.config.info.ascii, layer))


def show_layouts(kb_info_json, title_caps=True):
    """Render the layouts with info.json labels.
    """
    for layout_name, layout_art in render_layouts(kb_info_json, cli.config.info.ascii).items():
        title = layout_name.title() if title_caps else layout_name
        cli.echo('{fg_cyan}%s{fg_reset}:', title)
        print(layout_art)  # Avoid passing dirty data to cli.echo()


def show_matrix(kb_info_json, title_caps=True):
    """Render the layout with matrix labels in ascii art.
    """
    for layout_name, layout in kb_info_json['layouts'].items():
        # Build our label list
        labels = []
        for key in layout['layout']:
            if key['matrix']:
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
    if 'width' in kb_info_json and 'height' in kb_info_json:
        cli.echo('{fg_blue}Size{fg_reset}: %s x %s' % (kb_info_json['width'], kb_info_json['height']))
    cli.echo('{fg_blue}Processor{fg_reset}: %s', kb_info_json.get('processor', 'Unknown'))
    cli.echo('{fg_blue}Bootloader{fg_reset}: %s', kb_info_json.get('bootloader', 'Unknown'))

    if cli.config.info.layouts:
        show_layouts(kb_info_json, True)

    if cli.config.info.matrix:
        show_matrix(kb_info_json, True)

    if cli.config_source.info.keymap and cli.config_source.info.keymap != 'config_file':
        show_keymap(kb_info_json, True)


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


@cli.argument('-kb', '--keyboard', help='Keyboard to show info for.')
@cli.argument('-km', '--keymap', help='Show the layers for a JSON keymap too.')
@cli.argument('-l', '--layouts', action='store_true', help='Render the layouts.')
@cli.argument('-m', '--matrix', action='store_true', help='Render the layouts with matrix information.')
@cli.argument('-f', '--format', default='friendly', arg_only=True, help='Format to display the data in (friendly, text, json) (Default: friendly).')
@cli.argument('--ascii', action='store_true', default='windows' in platform_id, help='Render layout box drawings in ASCII only.')
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

    # Build the info.json file
    kb_info_json = info_json(cli.config.info.keyboard)

    # Output in the requested format
    if cli.args.format == 'json':
        print(json.dumps(kb_info_json))
    elif cli.args.format == 'text':
        print_text_output(kb_info_json)
    elif cli.args.format == 'friendly':
        print_friendly_output(kb_info_json)
    else:
        cli.log.error('Unknown format: %s', cli.args.format)
        return False
