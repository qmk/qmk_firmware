"""Compile and flash QMK Firmware

You can compile a keymap already in the repo or using a QMK Configurator export.
You can also specify makefile options.
"""
import json
import os
import sys
import subprocess
from argparse import FileType

from milc import cli

import qmk.keymap
import qmk.path

def print_bootloader_help():
    cli.log.error('You must supply a configuration file and bootloader,')
    cli.echo('or a -kb keyboard, -km keymap, and bootloader.')
    cli.echo('For example: qmk flash -kb planck/rev6 -km default dfu-util')
    cli.echo('or qmk flash 1upkeyboards_60hse_default.json dfu-util')
    cli.echo('For more info, visit https://docs.qmk.fm/#/flashing')
    cli.echo('Bootloaders:')
    cli.echo('dfu')
    cli.echo('dfu-ee')
    cli.echo('dfu-split-left')
    cli.echo('dfu-split-right')
    cli.echo('avrdude')
    cli.echo('BootloadHID')
    cli.echo('dfu-util')
    cli.echo('dfu-util-split-left')
    cli.echo('dfu-util-split-right')
    cli.echo('st-link-cli')

@cli.argument('bootloader', arg_only=True, help='The flash command, corresponding to qmk\'s make options of bootloaders.')
@cli.argument('filename', nargs='?', arg_only=True, help='The configurator export JSON to compile. Use this if you dont want to specify a keymap and keyboard.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Use this if you dont have a configurator file. Ignored when a configurator file is supplied.')
@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Use this if you dont have a configurator file. Ignored when a configurator file is supplied.')
@cli.subcommand('QMK FLash.')
def flash(cli):
    """Compile and or flash QMK Firmware or keyboard/layout

    If a Configurator JSON export is supplied this command will create a new keymap. Keymap and Keyboard arguments
    will be ignored.

    If no file is supplied, keymap and keyboard are expected.

    A bootloader is always required

    """
    if cli.args.filename:
        # Parse the configurator json
        file = open(cli.args.filename)
        user_keymap = json.load(file)
        file.close()

        # Generate the keymap
        keymap_path = qmk.path.keymap(user_keymap['keyboard'])
        cli.log.info('Creating {fg_cyan}%s{style_reset_all} keymap in {fg_cyan}%s', user_keymap['keymap'], keymap_path)
        qmk.keymap.write(user_keymap['keyboard'], user_keymap['keymap'], user_keymap['layout'], user_keymap['layers'])
        cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

        # Compile the keymap
        command = ['make', ':'.join((user_keymap['keyboard'], user_keymap['keymap'], cli.args.bootloader))]

    elif cli.args.keyboard and cli.args.keymap:
        # Generate the make command for a specific keyboard/keymap.
        command = ['make', ':'.join((cli.args.keyboard, cli.args.keymap, cli.args.bootloader))]

    else:
        print_bootloader_help()
        return False

    cli.log.info('Flashing keymap with {fg_cyan}%s\n\n', ' '.join(command))
    subprocess.run(command)