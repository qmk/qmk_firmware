"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
from subprocess import DEVNULL

from argcomplete.completers import FilesCompleter
from dotty_dict import dotty
from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import do_compile
from qmk.keyboard import keyboard_completer, is_keyboard_target
from qmk.keymap import keymap_completer
from qmk.metadata import true_values, false_values


@cli.argument('filename', nargs='?', arg_only=True, type=qmk.path.FileType('r'), completer=FilesCompleter('.json'), help='The configurator export to compile')
@cli.argument('-t', '--target', help="The make target to run. By default it compiles the keyboard only.")
@cli.argument('-kb', '--keyboard', type=is_keyboard_target, completer=keyboard_completer, help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs to run.")
@cli.argument('-f', '--filter', arg_only=True, action='append', default=[], help="Filter your list against info.json.")
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Set a variable to be passed to make. May be passed multiple times.")
@cli.argument('-c', '--clean', arg_only=True, action='store_true', help="Remove object files before compiling.")
@cli.subcommand('Compile a QMK Firmware.')
@automagic_keyboard
@automagic_keymap
def compile(cli):
    """Compile a QMK Firmware.

    If a Configurator export is supplied this command will create a new keymap, overwriting an existing keymap if one exists.

    If a keyboard and keymap are provided this command will build a firmware based on that.
    """
    # If -f has been specified without a keyboard target, assume -kb all
    keyboard = cli.config.compile.keyboard or ''

    if cli.args.filter and not cli.args.keyboard:
        cli.log.debug('--filter supplied without --keyboard, assuming --keyboard all.')
        keyboard = 'all'

    if cli.args.filename and cli.args.filter:
        cli.log.warning('Ignoring --filter because a keymap.json was provided.')

    filters = {}

    for filter in cli.args.filter:
        if '=' in filter:
            key, value = filter.split('=', 1)

            if value in true_values:
                value = True
            elif value in false_values:
                value = False
            elif value.isdigit():
                value = int(value)
            elif '.' in value and value.replace('.').isdigit():
                value = float(value)

            filters[key] = value

    return do_compile(keyboard, cli.config.compile.keymap, cli.config.compile.parallel, cli.config.compile.target, filters)
