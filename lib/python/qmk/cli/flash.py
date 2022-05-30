"""Compile and flash QMK Firmware

You can compile a keymap already in the repo or using a QMK Configurator export.
A bootloader must be specified.
"""
from subprocess import DEVNULL

from argcomplete.completers import FilesCompleter
from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import compile_configurator_json, create_make_command, parse_configurator_json
from qmk.keyboard import keyboard_completer, keyboard_folder


def print_bootloader_help():
    """Prints the available bootloaders listed in docs.qmk.fm.
    """
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


@cli.argument('filename', nargs='?', arg_only=True, type=qmk.path.FileType('r'), completer=FilesCompleter('.json'), help='The configurator export JSON to compile.')
@cli.argument('-b', '--bootloaders', action='store_true', help='List the available bootloaders.')
@cli.argument('-bl', '--bootloader', default='flash', help='The flash command, corresponding to qmk\'s make options of bootloaders.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Use this if you dont have a configurator file. Ignored when a configurator file is supplied.')
@cli.argument('-kb', '--keyboard', type=keyboard_folder, completer=keyboard_completer, help='The keyboard to build a firmware for. Use this if you dont have a configurator file. Ignored when a configurator file is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs; 0 means unlimited.")
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
    if cli.args.clean and not cli.args.filename and not cli.args.dry_run:
        command = create_make_command(cli.config.flash.keyboard, cli.config.flash.keymap, 'clean')
        cli.run(command, capture_output=False, stdin=DEVNULL)

    # Build the environment vars
    envs = {}
    for env in cli.args.env:
        if '=' in env:
            key, value = env.split('=', 1)
            envs[key] = value
        else:
            cli.log.warning('Invalid environment variable: %s', env)

    # Determine the compile command
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
        command = compile_configurator_json(user_keymap, cli.args.bootloader, parallel=cli.config.flash.parallel, **envs)

        cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

    else:
        if cli.config.flash.keyboard and cli.config.flash.keymap:
            # Generate the make command for a specific keyboard/keymap.
            command = create_make_command(cli.config.flash.keyboard, cli.config.flash.keymap, cli.args.bootloader, parallel=cli.config.flash.parallel, **envs)

        elif not cli.config.flash.keyboard:
            cli.log.error('Could not determine keyboard!')
        elif not cli.config.flash.keymap:
            cli.log.error('Could not determine keymap!')

    # Compile the firmware, if we're able to
    if command:
        cli.log.info('Compiling keymap with {fg_cyan}%s', ' '.join(command))
        if not cli.args.dry_run:
            cli.echo('\n')
            compile = cli.run(command, capture_output=False, stdin=DEVNULL)
            return compile.returncode

    else:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.echo('usage: qmk flash [-h] [-b] [-n] [-kb KEYBOARD] [-km KEYMAP] [-bl BOOTLOADER] [filename]')
        return False
