"""Generate a keymap.c from a configurator export.
"""
import json
import os
import sys

from milc import cli

import qmk.keymap


@cli.argument('-o', '--output', arg_only=True, help='File to write to')
@cli.argument('filename', arg_only=True, help='Configurator JSON file')
@cli.subcommand('Create a keymap.c from a QMK Configurator export.')
def json_keymap(cli):
    """Generate a keymap.c from a configurator export.

    This command uses the `qmk.keymap` module to generate a keymap.c from a configurator export. The generated keymap is written to stdout, or to a file if -o is provided.
    """
    # Error checking
    if cli.args.filename == ('-'):
        cli.log.error('Reading from STDIN is not (yet) supported.')
        cli.print_usage()
        exit(1)
    if not os.path.exists(qmk.path.normpath(cli.args.filename)):
        cli.log.error('JSON file does not exist!')
        cli.print_usage()
        exit(1)

    # Environment processing
    if cli.args.output == ('-'):
        cli.args.output = None

    # Parse the configurator json
    with open(qmk.path.normpath(cli.args.filename), 'r') as fd:
        user_keymap = json.load(fd)

    # Generate the keymap
    keymap_c = qmk.keymap.generate(user_keymap['keyboard'], user_keymap['layout'], user_keymap['layers'])

    if cli.args.output:
        output_dir = os.path.dirname(cli.args.output)

        if not os.path.exists(output_dir):
            os.makedirs(output_dir)

        output_file = qmk.path.normpath(cli.args.output)
        with open(output_file, 'w') as keymap_fd:
            keymap_fd.write(keymap_c)

        cli.log.info('Wrote keymap to %s.', cli.args.output)

    else:
        print(keymap_c)
