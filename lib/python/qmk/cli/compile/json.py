"""Create a keymap directory from a configurator export.
"""
import json
import os
import sys
import subprocess

import qmk.keymap
from milc import cli


@cli.argument('-f', '--filename', help='Configurator JSON export', required=True)  # FIXME: This should be positional
@cli.entrypoint('Generate a keymap.c from a QMK Configurator export.')
def main(cli):
    # Error checking
    if cli.config.general.filename == ('-'):
        cli.log.error('Reading from STDIN is not (yet) supported.')
        cli.print_usage()
    if not os.path.exists(cli.config.general.filename):
        cli.log.error('JSON file does not exist!')
        cli.print_usage()

    # Parse the configurator json
    with open(cli.config.general.filename, 'r') as fd:
        user_keymap = json.load(fd)

    # Generate the keymap
    qmk.keymap.write(user_keymap['keyboard'], user_keymap['keymap'], user_keymap['layout'], user_keymap['layers'])
    if sys.stdout.isatty():
        keymap_path = qmk.keymap.find_dir(user_keymap['keyboard'])
        cli.echo('Wrote keymap to %s/%s/keymap.c.', keymap_path, user_keymap['keymap'])

    # Compile the keymap
    command = ['make', ':'.join((user_keymap['keyboard'], user_keymap['keymap']))]
    cli.echo('Compiling keymap with `%s`:', ' '.join(command))
    subprocess.run(command)
