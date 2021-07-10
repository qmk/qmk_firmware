"""Compile and flash QMK Firmware

You can compile a keymap already in the repo or using a QMK Configurator export.
A bootloader must be specified.
"""
from subprocess import DEVNULL

from argcomplete.completers import FilesCompleter
from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import do_compile
from qmk.keyboard import keyboard_completer, is_keyboard_target


def print_bootloader_help():
    """Prints the available bootloaders listed in docs.qmk.fm.
    """
    cli.log.info('Here are the available bootloaders:')
    cli.echo('\tdfu')
    cli.echo('\tdfu-ee')
    cli.echo('\tdfu-split-left')
    cli.echo('\tdfu-split-right')
    cli.echo('\tavrdude')
    cli.echo('\tBootloadHID')
    cli.echo('\tdfu-util')
    cli.echo('\tdfu-util-split-left')
    cli.echo('\tdfu-util-split-right')
    cli.echo('\tst-link-cli')
    cli.echo('\tst-flash')
    cli.echo('For more info, visit https://docs.qmk.fm/#/flashing')


@cli.argument('filename', nargs='?', arg_only=True, type=qmk.path.FileType('r'), completer=FilesCompleter('.json'), help='The configurator export JSON to compile.')
@cli.argument('-b', '--bootloaders', action='store_true', help='List the available bootloaders.')
@cli.argument('-bl', '--bootloader', default='flash', help='The flash command, corresponding to qmk\'s make options of bootloaders.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Use this if you dont have a configurator file. Ignored when a configurator file is supplied.')
@cli.argument('-kb', '--keyboard', type=is_keyboard_target, completer=keyboard_completer, help='The keyboard to build a firmware for. Use this if you dont have a configurator file. Ignored when a configurator file is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs to run.")
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Set a variable to be passed to make. May be passed multiple times.")
@cli.argument('-c', '--clean', arg_only=True, action='store_true', help="Remove object files before compiling.")
@cli.subcommand('QMK Flash.')
@automagic_keyboard
@automagic_keymap
def flash(cli):
    """Compile and or flash QMK Firmware or keyboard/layout

    If a Configurator JSON export is supplied this command will create a new keymap. Keymap and Keyboard arguments
    will be ignored.

    If no file is supplied, keymap and keyboard are expected.

    If bootloader is omitted the make system will use the configured bootloader for that keyboard.
    """
    if cli.args.bootloaders:
        # Provide usage and list bootloaders
        cli.print_usage()
        print_bootloader_help()
        return False

    return do_compile(cli.config.flash.keyboard, cli.config.flash.keymap, cli.config.flash.parallel, cli.config.flash.bootloader)