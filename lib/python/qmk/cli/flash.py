"""Compile and flash QMK Firmware

You can compile a keymap already in the repo or using a QMK Configurator export.
A bootloader must be specified.
"""
import subprocess
from argparse import FileType

from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import compile_configurator_json, create_make_command, parse_configurator_json


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


@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), help='The configurator export JSON to compile.')
@cli.argument('-b', '--bootloaders', action='store_true', help='List the available bootloaders.')
@cli.argument('-bl', '--bootloader', default='flash', help='The flash command, corresponding to qmk\'s make options of bootloaders.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Use this if you dont have a configurator file. Ignored when a configurator file is supplied.')
@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Use this if you dont have a configurator file. Ignored when a configurator file is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
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
    command = ''

    if cli.args.bootloaders:
        # Provide usage and list bootloaders
        cli.echo('usage: qmk flash [-h] [-b] [-n] [-kb KEYBOARD] [-km KEYMAP] [-bl BOOTLOADER] [filename]')
        print_bootloader_help()
        return False

    if cli.args.filename:
        # Handle compiling a configurator JSON
        user_keymap = parse_configurator_json(cli.args.filename)
        keymap_path = qmk.path.keymap(user_keymap['keyboard'])
        command = compile_configurator_json(user_keymap, cli.args.bootloader)

        cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

    else:
        if cli.config.flash.keyboard and cli.config.flash.keymap:
            # Generate the make command for a specific keyboard/keymap.
            command = create_make_command(cli.config.flash.keyboard, cli.config.flash.keymap, cli.args.bootloader)

        elif not cli.config.flash.keyboard:
            cli.log.error('Could not determine keyboard!')
        elif not cli.config.flash.keymap:
            cli.log.error('Could not determine keymap!')

    # Compile the firmware, if we're able to
    if command:
        cli.log.info('Compiling keymap with {fg_cyan}%s', ' '.join(command))
        if not cli.args.dry_run:
            cli.echo('\n')
            subprocess.run(command)

    else:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.echo('usage: qmk flash [-h] [-b] [-n] [-kb KEYBOARD] [-km KEYMAP] [-bl BOOTLOADER] [filename]')
        return False
