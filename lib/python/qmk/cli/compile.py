"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
import subprocess
from argparse import FileType

from milc import cli
from qmk.commands import create_make_command
from qmk.commands import parse_configurator_json
from qmk.commands import compile_configurator_json
from qmk.commands import compile_configurator_json_encoders

import qmk.keymap
import qmk.path


@cli.argument('filename', nargs='?', type=FileType('r'), help='The configurator export to compile')
@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-x', '--experimental', action='store_true', help='True enables encoder support for configurator export files. Only enabled when a configurator export is supplied.')
@cli.subcommand('Compile a QMK Firmware.')
def compile(cli):
    """Compile a QMK Firmware.

    If a Configurator export is supplied this command will create a new keymap, overwriting an existing keymap if one exists.

    FIXME(skullydazed): add code to check and warn if the keymap already exists

    If --keyboard and --keymap are provided this command will build a firmware based on that.

    """
    experimental_mode = False

    if cli.args.filename and cli.args.experimental:

        # Warn the user
        cli.log.info("{fg_yellow}Compiling in experimental mode!")
        cont = input('Are you sure? Y/N ')

        experimental_mode = False
        if (cont.lower() == 'y' or cont.lower() == 'yes'):
          experimental_mode = True

    if cli.args.filename:
        # Parse the configurator json
        user_keymap = parse_configurator_json(cli.args.filename)

        # Generate the keymap
        keymap_path = qmk.path.keymap(user_keymap['keyboard'])
        cli.log.info('Creating {fg_cyan}%s{style_reset_all} keymap in {fg_cyan}%s', user_keymap['keymap'], keymap_path)

        # Compile the keymap
        command = compile_configurator_json(user_keymap)
        if experimental_mode:
          command = compile_configurator_json_encoders(user_keymap)

        cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

    elif cli.config.compile.keyboard and cli.config.compile.keymap:
        # Generate the make command for a specific keyboard/keymap.
        command = create_make_command(cli.config.compile.keyboard, cli.config.compile.keymap)

    else:
        cli.log.error('You must supply a configurator export or both `--keyboard` and `--keymap`.')
        return False

    cli.log.info('Compiling keymap with {fg_cyan}%s\n\n', ' '.join(command))
    subprocess.run(command)
