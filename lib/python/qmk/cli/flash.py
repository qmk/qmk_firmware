"""Compile and flash QMK Firmware

You can compile a keymap already in the repo or using a QMK Configurator export.
A bootloader must be specified.
"""
from argcomplete.completers import FilesCompleter
from pathlib import Path

from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import build_environment
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.keymap import keymap_completer, locate_keymap
from qmk.flashers import flasher
from qmk.build_targets import KeyboardKeymapBuildTarget, JsonKeymapBuildTarget


def _list_bootloaders():
    """Prints the available bootloaders listed in docs.qmk.fm.
    """
    cli.print_help()
    cli.log.info('Here are the available bootloaders:')
    cli.echo('\tavrdude')
    cli.echo('\tbootloadhid')
    cli.echo('\tdfu')
    cli.echo('\tdfu-util')
    cli.echo('\tmdloader')
    cli.echo('\tst-flash')
    cli.echo('\tst-link-cli')
    cli.log.info('Enhanced variants for split keyboards:')
    cli.echo('\tavrdude-split-left')
    cli.echo('\tavrdude-split-right')
    cli.echo('\tdfu-ee')
    cli.echo('\tdfu-split-left')
    cli.echo('\tdfu-split-right')
    cli.echo('\tdfu-util-split-left')
    cli.echo('\tdfu-util-split-right')
    cli.echo('\tuf2-split-left')
    cli.echo('\tuf2-split-right')
    cli.echo('For more info, visit https://docs.qmk.fm/#/flashing')
    return False


def _flash_binary(filename, mcu):
    """Try to flash binary firmware
    """
    cli.echo('Flashing binary firmware...\nPlease reset your keyboard into bootloader mode now!\nPress Ctrl-C to exit.\n')
    try:
        err, msg = flasher(mcu, filename)
        if err:
            cli.log.error(msg)
            return False
    except KeyboardInterrupt:
        cli.log.info('Ctrl-C was pressed, exiting...')
    return True


@cli.argument('filename', nargs='?', arg_only=True, type=qmk.path.FileType('r'), completer=FilesCompleter('.json'), help='A configurator export JSON to be compiled and flashed or a pre-compiled binary firmware file (bin/hex) to be flashed.')
@cli.argument('-b', '--bootloaders', action='store_true', help='List the available bootloaders.')
@cli.argument('-bl', '--bootloader', default='flash', help='The flash command, corresponding to qmk\'s make options of bootloaders.')
@cli.argument('-m', '--mcu', help='The MCU name. Required for HalfKay, HID, USBAspLoader and ISP flashing.')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs; 0 means unlimited.")
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Set a variable to be passed to make. May be passed multiple times.")
@cli.argument('-c', '--clean', arg_only=True, action='store_true', help="Remove object files before compiling.")
@cli.subcommand('QMK Flash.')
@automagic_keyboard
@automagic_keymap
def flash(cli):
    """Compile and or flash QMK Firmware or keyboard/layout

    If a binary firmware is supplied, try to flash that.

    If a Configurator export is supplied this command will create a new keymap, overwriting an existing keymap if one exists.

    If a keyboard and keymap are provided this command will build a firmware based on that.

    If bootloader is omitted the make system will use the configured bootloader for that keyboard.
    """
    if cli.args.filename and isinstance(cli.args.filename, Path) and cli.args.filename.suffix in ['.bin', '.hex', '.uf2']:
        return _flash_binary(cli.args.filename, cli.args.mcu)

    if cli.args.bootloaders:
        return _list_bootloaders()

    # Build the environment vars
    envs = build_environment(cli.args.env)

    # Handler for the build target
    target = None

    if cli.args.filename:
        # if we were given a filename, assume we have a json build target
        target = JsonKeymapBuildTarget(cli.args.filename)

    elif cli.config.flash.keyboard and cli.config.flash.keymap:
        # if we got a keyboard and keymap, attempt to find it
        if not locate_keymap(cli.config.flash.keyboard, cli.config.flash.keymap):
            cli.log.error('Invalid keymap argument.')
            cli.print_help()
            return False

        # If we got here, then we have a valid keyboard and keymap for a build target
        target = KeyboardKeymapBuildTarget(cli.config.flash.keyboard, cli.config.flash.keymap)

    if not target:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.print_help()
        return False

    target.configure(parallel=cli.config.flash.parallel, clean=cli.args.clean)
    return target.compile(cli.args.bootloader, dry_run=cli.args.dry_run, **envs)
