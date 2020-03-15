"""Compile and flash QMK Firmware

You can compile a keymap already in the repo or using a QMK Configurator export.
A bootloader must be specified.
"""
import subprocess
from argparse import FileType

import qmk.path
from milc import cli
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
    cli.echo('For more info, visit https://docs.qmk.fm/#/flashing')


@cli.argument('-bl', '--bootloader', default='flash', help='The flash command, corresponding to qmk\'s make options of bootloaders.')
@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), help='The configurator export JSON to compile.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Use this if you dont have a configurator file. Ignored when a configurator file is supplied.')
@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Use this if you dont have a configurator file. Ignored when a configurator file is supplied.')
@cli.argument('-b', '--bootloaders', action='store_true', help='List the available bootloaders.')
@cli.argument('-x', '--experimental', help='Compiles configurator json with encoder support. Only supported for use with the `filename` parameter')
@cli.subcommand('QMK Flash.')
def flash(cli):
    """Compile and or flash QMK Firmware or keyboard/layout

    If a Configurator JSON export is supplied this command will create a new keymap. Keymap and Keyboard arguments
    will be ignored.

    If no file is supplied, keymap and keyboard are expected.

    If bootloader is omitted, the one according to the rules.mk will be used.

    """
    command = []
    if cli.args.bootloaders:
        # Provide usage and list bootloaders
        cli.echo('usage: qmk flash [-h] [-b] [-kb KEYBOARD] [-km KEYMAP] [-bl BOOTLOADER] [filename]')
        print_bootloader_help()
        return False

    elif cli.args.keymap and not cli.args.keyboard:
        # If only a keymap was given but no keyboard, suggest listing keyboards
        cli.echo('usage: qmk flash [-h] [-b] [-kb KEYBOARD] [-km KEYMAP] [-bl BOOTLOADER] [filename]')
        cli.log.error('run \'qmk list_keyboards\' to find out the supported keyboards')
        return False

    elif cli.args.filename:
        # Get keymap path to log info
        user_keymap = parse_configurator_json(cli.args.filename)
        keymap_path = qmk.path.keymap(user_keymap['keyboard'])

        use_encoders = False
        if cli.args.experimental:
          use_encoders = True

        cli.log.info('Creating {fg_cyan}%s{style_reset_all} keymap in {fg_cyan}%s', user_keymap['keymap'], keymap_path)

        # Convert the JSON into a C file and write it to disk.
        command = compile_configurator_json(user_keymap, cli.args.bootloader)
        if cli.args.experimental:
          command = compile_configurator_json_encoders(users_keymap, cli.args.bootloader)

        cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

    elif cli.args.keyboard and cli.args.keymap:
        # Generate the make command for a specific keyboard/keymap.
        command = create_make_command(cli.config.flash.keyboard, cli.config.flash.keymap, cli.args.bootloader)

    else:
        cli.echo('usage: qmk flash [-h] [-b] [-kb KEYBOARD] [-km KEYMAP] [-bl BOOTLOADER] [filename]')
        cli.log.error('You must supply a configurator export or both `--keyboard` and `--keymap`. You can also specify a bootloader with --bootloader. Use --bootloaders to list the available bootloaders.')
        return False

    cli.log.info('Flashing keymap with {fg_cyan}%s\n\n', ' '.join(command))
    subprocess.run(command)
