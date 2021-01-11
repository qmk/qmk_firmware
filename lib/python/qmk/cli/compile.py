"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
import json
import os
import sys
import subprocess
from argparse import FileType

from milc import cli

import qmk.keymap
import qmk.path


@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), help='The configurator export to compile')
@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.subcommand('Compile a QMK Firmware.')
def compile(cli):
    """Compile a QMK Firmware.

    If a Configurator export is supplied this command will create a new keymap, overwriting an existing keymap if one exists.

    FIXME(skullydazed): add code to check and warn if the keymap already exists

    If --keyboard and --keymap are provided this command will build a firmware based on that.

    """
    if cli.args.filename:
        # Parse the configurator json
        user_keymap = json.load(cli.args.filename)

        # Generate the keymap
        keymap_path = qmk.path.keymap(user_keymap['keyboard'])
        cli.log.info('Creating {fg_cyan}%s{style_reset_all} keymap in {fg_cyan}%s', user_keymap['keymap'], keymap_path)
        qmk.keymap.write(user_keymap['keyboard'], user_keymap['keymap'], user_keymap['layout'], user_keymap['layers'])
        cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

        # Compile the keymap
        command = ['make', ':'.join((user_keymap['keyboard'], user_keymap['keymap']))]

    elif cli.config.compile.keyboard and cli.config.compile.keymap:
        # Generate the make command for a specific keyboard/keymap.
        command = ['make', ':'.join((cli.config.compile.keyboard, cli.config.compile.keymap))]

    else:
        cli.log.error('You must supply a configurator export or both `--keyboard` and `--keymap`.')
        return False

    cli.log.info('Compiling keymap with {fg_cyan}%s\n\n', ' '.join(command))
    subprocess.run(command)
