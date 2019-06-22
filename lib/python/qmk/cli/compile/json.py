"""Create a keymap directory from a configurator export.
"""
import json
import os
import sys
import subprocess

from milc import cli

import qmk.keymap


@cli.argument('filename', help='Configurator JSON export')
@cli.entrypoint('Generate a keymap.c from a QMK Configurator export.')
def main(cli):
    # Error checking
    if cli.args.filename == ('-'):
        cli.log.error('Reading from STDIN is not (yet) supported.')
        cli.print_usage()
    if not os.path.exists(cli.args.filename):
        cli.log.error('JSON file does not exist!')
        cli.print_usage()

    # Parse the configurator json
    with open(cli.args.filename, 'r') as fd:
        user_keymap = json.load(fd)

    # Generate the keymap
    keymap_path = qmk.keymap.find_dir(user_keymap['keyboard'])
    cli.echo('{fg_blue}[QMK]{style_reset_all} Creating {fg_cyan}%s{style_reset_all} keymap in {fg_cyan}%s', user_keymap['keymap'], keymap_path)
    qmk.keymap.write(user_keymap['keyboard'], user_keymap['keymap'], user_keymap['layout'], user_keymap['layers'])
    cli.echo('{fg_blue}[QMK]{style_reset_all} Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

    # Compile the keymap
    command = ['make', ':'.join((user_keymap['keyboard'], user_keymap['keymap']))]
    cli.echo('{fg_blue}[QMK]{style_reset_all} Compiling keymap with {fg_cyan}%s\n\n', ' '.join(command))
    subprocess.run(command)
