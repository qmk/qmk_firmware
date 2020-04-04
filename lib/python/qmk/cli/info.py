"""Keyboard information script.

Compile an info.json for a particular keyboard and pretty-print it.
"""
import json

from milc import cli

from qmk.decorators import automagic_keyboard
from qmk.keyboard import is_keyboard, render_layouts
from qmk.path import info_json


@cli.argument('-l', '--layouts', action='store_true', help='Render the layouts.')
@cli.argument('-kb', '--keyboard', help='Keyboard to show info for.')
@cli.argument('-f', '--format', default='friendly', arg_only=True, help='Format to display the data in (friendly, text, json) (Default: friendly).')
@cli.subcommand('Keyboard information.')
@automagic_keyboard
def info(cli):
    """Compile an info.json for a particular keyboard and pretty-print it.
    """
    # Determine our keyboard(s)
    if not is_keyboard(cli.config.info.keyboard):
        cli.log.error('Invalid keyboard: %s!', cli.config.info.keyboard)
        exit(1)

    # Build the info.json file
    kb_info_json = info_json(cli.config.info.keyboard)

    # Output in the requested format
    if cli.args.format == 'json':
        print(json.dumps(kb_info_json))

    elif cli.args.format == 'text':
        for key in sorted(kb_info_json):
            if key == 'layouts':
                cli.echo('{fg_blue}layouts{fg_reset}: %s', ', '.join(sorted(kb_info_json['layouts'].keys())))
            else:
                cli.echo('{fg_blue}%s{fg_reset}: %s', key, kb_info_json[key])

        if cli.config.info.layouts:
            for layout_name, layout_art in render_layouts(kb_info_json).items():
                cli.echo('{fg_cyan}%s{fg_reset}:', layout_name)
                print(layout_art)  # Avoid passing dirty data to cli.echo()

    elif cli.args.format == 'friendly':
        cli.echo('{fg_blue}Keyboard Name{fg_reset}: %s', kb_info_json.get('keyboard_name', 'Unknown'))
        cli.echo('{fg_blue}Manufacturer{fg_reset}: %s', kb_info_json.get('manufacturer', 'Unknown'))
        if 'url' in kb_info_json:
            cli.echo('{fg_blue}Website{fg_reset}: %s', kb_info_json['url'])
        if kb_info_json.get('maintainer') == 'qmk':
            cli.echo('{fg_blue}Maintainer{fg_reset}: QMK Community')
        else:
            cli.echo('{fg_blue}Maintainer{fg_reset}: %s', kb_info_json.get('maintainer', 'qmk'))
        cli.echo('{fg_blue}Keyboard Folder{fg_reset}: %s', kb_info_json.get('keyboard_folder', 'Unknown'))
        cli.echo('{fg_blue}Layouts{fg_reset}: %s', ', '.join(sorted(kb_info_json['layouts'].keys())))
        if 'width' in kb_info_json and 'height' in kb_info_json:
            cli.echo('{fg_blue}Size{fg_reset}: %s x %s' % (kb_info_json['width'], kb_info_json['height']))
        cli.echo('{fg_blue}Processor{fg_reset}: %s', kb_info_json.get('processor', 'Unknown'))
        cli.echo('{fg_blue}Bootloader{fg_reset}: %s', kb_info_json.get('bootloader', 'Unknown'))

        if cli.config.info.layouts:
            for layout_name, layout_art in render_layouts(kb_info_json).items():
                cli.echo('{fg_cyan}%s{fg_reset}:', layout_name)
                print(layout_art)  # Avoid passing dirty data to cli.echo()

    else:
        cli.log.error('Unknown format: %s', cli.args.format)
