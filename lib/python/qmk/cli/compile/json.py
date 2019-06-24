"""Create a keymap directory from a configurator export.
"""
import json
import os
import sys
import subprocess

from milc import cli

import qmk.keymap
import qmk.path


@cli.argument('filename', help='Configurator JSON export')
@cli.entrypoint('Compile a QMK Configurator export.')
def main(cli):
    """Compile a QMK Configurator export.

    This command creates a new keymap from a configurator export, overwriting an existing keymap if one exists.

    FIXME(skullydazed): add code to check and warn if the keymap already exists
    """
    # Error checking
    if cli.args.filename == ('-'):
        cli.log.error('Reading from STDIN is not (yet) supported.')
        exit(1)
    if not os.path.exists(qmk.path.normpath(cli.args.filename)):
        cli.log.error('JSON file does not exist!')
        exit(1)

    # Parse the configurator json
    with open(qmk.path.normpath(cli.args.filename), 'r') as fd:
        user_keymap = json.load(fd)

    # Generate the keymap
    keymap_path = qmk.path.keymap(user_keymap['keyboard'])
    cli.log.info('Creating {fg_cyan}%s{style_reset_all} keymap in {fg_cyan}%s', user_keymap['keymap'], keymap_path)
    qmk.keymap.write(user_keymap['keyboard'], user_keymap['keymap'], user_keymap['layout'], user_keymap['layers'])
    cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

    # Compile the keymap
    command = ['make', ':'.join((user_keymap['keyboard'], user_keymap['keymap']))]
    cli.log.info('Compiling keymap with {fg_cyan}%s\n\n', ' '.join(command))
    subprocess.run(command)
