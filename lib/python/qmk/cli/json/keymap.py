"""Generate a keymap.c from a configurator export.
"""
import json
import os
import sys

from milc import cli

import qmk.keymap


@cli.argument('filename', help='Configurator JSON file')
@cli.argument('-o', '--output', help='File to write to')
@cli.entrypoint('Generate a keymap.c from a QMK Configurator export.')
def main(cli):
    # Error checking
    if cli.args.filename == ('-'):
        cli.log.error('Reading from STDIN is not (yet) supported.')
        cli.print_usage()
    if not os.path.exists(cli.args.filename):
        cli.log.error('JSON file does not exist!')
        cli.print_usage()

    # Environment processing
    if cli.args.output == ('-'):
        cli.args.output = None

    # Parse the configurator json
    with open(cli.args.filename, 'r') as fd:
        user_keymap = json.load(fd)

    # Generate the keymap
    keymap_c = qmk.keymap.generate(user_keymap['keyboard'], user_keymap['layout'], user_keymap['layers'])

    if cli.args.output:
        output_dir = os.path.dirname(cli.args.output)

        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        with open(cli.args.output, 'w') as keymap_fd:
            keymap_fd.write(keymap_c)

        if sys.stdout.isatty():
            cli.echo('Wrote keymap to %s.', cli.args.output)

    else:
        cli.echo(keymap_c)
