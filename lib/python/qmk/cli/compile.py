"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
import subprocess
from argparse import FileType

from milc import cli

import qmk.path
from qmk.commands import compile_configurator_json, create_make_command, find_keyboard_keymap, parse_configurator_json


@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), help='The configurator export to compile')
@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.subcommand('Compile a QMK Firmware.')
def compile(cli):
    """Compile a QMK Firmware.

    If a Configurator export is supplied this command will create a new keymap, overwriting an existing keymap if one exists.

    If a keyboard and keymap are provided this command will build a firmware based on that.
    """
    if cli.args.filename:
        # If a configurator JSON was provided skip straight to compiling it
        # FIXME(skullydazed): add code to check and warn if the keymap already exists when compiling a json keymap.
        user_keymap = parse_configurator_json(cli.args.filename)
        keymap_path = qmk.path.keymap(user_keymap['keyboard'])
        command = compile_configurator_json(user_keymap)

        cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

    else:
        # Perform the action the user specified
        user_keyboard, user_keymap = find_keyboard_keymap()
        if user_keyboard and user_keymap:
            # Generate the make command for a specific keyboard/keymap.
            command = create_make_command(user_keyboard, user_keymap)

        else:
            cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
            cli.echo('usage: qmk compile [-h] [-b] [-kb KEYBOARD] [-km KEYMAP] [filename]')
            return False

    cli.log.info('Compiling keymap with {fg_cyan}%s\n\n', ' '.join(command))
    subprocess.run(command)
