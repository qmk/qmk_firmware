"""Generate a keymap.c from a configurator export.
"""
import json
import os
import sys

import qmk.keymap
from milc import cli


@cli.argument('-f', '--filename', help='Configurator JSON export', required=True)  # FIXME: This should be positional
@cli.argument('-o', '--output', help='File to write to')
@cli.entrypoint('Generate a keymap.c from a QMK Configurator export.')
def main(cli):
    # Error checking
    if cli.config.general.filename == ('-'):
        cli.log.error('Reading from STDIN is not (yet) supported.')
        cli.print_usage()
    if not os.path.exists(cli.config.general.filename):
        cli.log.error('JSON file does not exist!')
        cli.print_usage()

    # Environment processing
    if cli.config.general.output == ('-'):
        cli.config.general.output = None

    # Parse the configurator json
    with open(cli.config.general.filename, 'r') as fd:
        user_keymap = json.load(fd)

    # Generate the keymap
    keymap_c = qmk.keymap.generate(user_keymap['keyboard'], user_keymap['layout'], user_keymap['layers'])

    if cli.config.general.output:
        with open(cli.config.general.output, 'w') as keymap_fd:
            keymap_fd.write(keymap_c)

        if sys.stdout.isatty():
            cli.echo('Wrote keymap to %s.', cli.config.general.output)

    else:
        cli.echo(keymap_c)
