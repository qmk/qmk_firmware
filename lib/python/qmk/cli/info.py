"""Keyboard information script.

Compile an info.json for a particular keyboard and pretty-print it.
"""
import json
import os
from pathlib import Path
from time import strftime

from milc import cli

from qmk.keyboard import is_keyboard
from qmk.path import info_json


@cli.argument('keyboards', nargs='*', arg_only=True, help='Keyboard to show info for.')
@cli.argument('-f', '--format', default='friendly', arg_only=True, help='Format to display the data in (friendly, text, json) (Default: friendly).')
@cli.subcommand('Keyboard information.')
def info(cli):
    """Compile an info.json for a particular keyboard and pretty-print it.
    """
    # Determine our keyboard(s)
    if not cli.args.keyboards:
        if '/qmk_firmware/keyboards/' in os.environ.get('ORIG_CWD'):
            cwd = Path(os.environ.get('ORIG_CWD'))
            qmk_firmware = Path(os.getcwd()) / 'keyboards'
            cli.args.keyboards = [cwd.relative_to(qmk_firmware)]
        else:
            cli.log.error('No keyboard supplied!')
            cli.print_usage()  # FIXME(skullydazed): milc should return the subcommand help here, and isn't
            exit(1)

    # Build the info.json file
    full_info_json = {'git_hash': 'FIXME', 'last_updated': strftime('%Y-%m-%d %H:%M:%S %z'), 'keyboards': {}}
    for keyboard in cli.args.keyboards:
        if not is_keyboard(keyboard):
            cli.log.error('Unknown keyboard: %s', keyboard)
            continue

        full_info_json['keyboards'][str(keyboard)] = info_json(keyboard)

    if cli.args.format == 'json':
        print(json.dumps(full_info_json))

    elif cli.args.format == 'text':
        for keyboard in full_info_json['keyboards'].values():
            cli.echo('{fg_blue}%s:', keyboard['keyboard_folder'])
            for key in sorted(keyboard):
                if key == 'layouts':
                    cli.echo('\t{fg_lightcyan_ex}layouts{fg_reset}: %s', ', '.join(sorted(keyboard['layouts'].keys())))
                else:
                    cli.echo('\t{fg_lightcyan_ex}%s{fg_reset}: %s', key, keyboard[key])

    elif cli.args.format == 'friendly':
        for count, keyboard in enumerate(full_info_json['keyboards'].values()):
            if count > 0:
                cli.echo('')

            cli.echo('{fg_blue}Keyboard Name{fg_reset}: %s', keyboard.get('keyboard_name', 'Unknown'))
            cli.echo('{fg_blue}Manufacturer{fg_reset}: %s', keyboard.get('manufacturer', 'Unknown'))
            if 'url' in keyboard:
                cli.echo('{fg_blue}Website{fg_reset}: %s', keyboard['url'])
            if keyboard.get('maintainer') == 'qmk':
                cli.echo('{fg_blue}Maintainer{fg_reset}: QMK Community')
            else:
                cli.echo('{fg_blue}Maintainer{fg_reset}: %s', keyboard.get('maintainer', 'qmk'))
            cli.echo('{fg_blue}Keyboard Folder{fg_reset}: %s', keyboard.get('keyboard_folder', 'Unknown'))
            cli.echo('{fg_blue}Layouts{fg_reset}: %s', ', '.join(sorted(keyboard['layouts'].keys())))
            if 'width' in keyboard and 'height' in keyboard:
                cli.echo('{fg_blue}Size{fg_reset}: %s x %s' % (keyboard['width'], keyboard['height']))
            cli.echo('{fg_blue}Processor{fg_reset}: %s', keyboard.get('processor', 'Unknown'))
            cli.echo('{fg_blue}Bootloader{fg_reset}: %s', keyboard.get('bootloader', 'Unknown'))

    else:
        cli.log.error('Unknown format: %s', cli.args.format)
