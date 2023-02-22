"""Compile and flash QMK Firmware

You can compile a keymap already in the repo or using a QMK Configurator export.
A bootloader must be specified.
"""
from argcomplete.completers import FilesCompleter

from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import compile_configurator_json, create_make_command, parse_configurator_json, build_environment
from qmk.keyboard import keyboard_completer, keyboard_folder
from qmk.flashers import flasher


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


@cli.argument('filename', nargs='?', arg_only=True, type=qmk.path.FileType('r'), completer=FilesCompleter('.json'), help='A configurator export JSON to be compiled and flashed or a pre-compiled binary firmware file (bin/hex) to be flashed.')
@cli.argument('-b', '--bootloaders', action='store_true', help='List the available bootloaders.')
@cli.argument('-bl', '--bootloader', default='flash', help='The flash command, corresponding to qmk\'s make options of bootloaders.')
@cli.argument('-m', '--mcu', help='The MCU name. Required for HalfKay, HID, USBAspLoader and ISP flashing.')
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

    If a binary firmware is supplied, try to flash that.

    If a Configurator JSON export is supplied this command will create a new keymap. Keymap and Keyboard arguments
    will be ignored.

    If no file is supplied, keymap and keyboard are expected.

    If bootloader is omitted the make system will use the configured bootloader for that keyboard.
    """
    if cli.args.filename and cli.args.filename.suffix in ['.bin', '.hex']:
        # Try to flash binary firmware
        cli.echo('Flashing binary firmware...\nPlease reset your keyboard into bootloader mode now!\nPress Ctrl-C to exit.\n')
        try:
            err, msg = flasher(cli.args.mcu, cli.args.filename)
            if err:
                cli.log.error(msg)
                return False
        except KeyboardInterrupt:
            cli.log.info('Ctrl-C was pressed, exiting...')
        return True

    if cli.args.bootloaders:
        # Provide usage and list bootloaders
        cli.print_help()
        print_bootloader_help()
        return False

    # Build the environment vars
    envs = build_environment(cli.args.env)

    # Determine the compile command
    commands = []

    if cli.args.filename:
        # If a configurator JSON was provided generate a keymap and compile it
        user_keymap = parse_configurator_json(cli.args.filename)
        commands = [compile_configurator_json(user_keymap, cli.args.bootloader, parallel=cli.config.flash.parallel, clean=cli.args.clean, **envs)]

    elif cli.config.flash.keyboard and cli.config.flash.keymap:
        # Generate the make command for a specific keyboard/keymap.
        if cli.args.clean:
            commands.append(create_make_command(cli.config.flash.keyboard, cli.config.flash.keymap, 'clean', **envs))
        commands.append(create_make_command(cli.config.flash.keyboard, cli.config.flash.keymap, cli.args.bootloader, parallel=cli.config.flash.parallel, **envs))

    if not commands:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.print_help()
        return False

    cli.log.info('Compiling keymap with {fg_cyan}%s', ' '.join(commands[-1]))
    if not cli.args.dry_run:
        cli.echo('\n')
        for command in commands:
            ret = cli.run(command, capture_output=False)
            if ret.returncode:
                return ret.returncode
