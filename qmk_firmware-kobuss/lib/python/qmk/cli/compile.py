"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
import subprocess
from argparse import FileType

from milc import cli

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import compile_configurator_json, create_make_command, parse_configurator_json


@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), help='The configurator export to compile')
@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
@cli.subcommand('Compile a QMK Firmware.')
@automagic_keyboard
@automagic_keymap
def compile(cli):
    """Compile a QMK Firmware.

    If a Configurator export is supplied this command will create a new keymap, overwriting an existing keymap if one exists.

    If a keyboard and keymap are provided this command will build a firmware based on that.
    """
    command = None

    if cli.args.filename:
        # If a configurator JSON was provided generate a keymap and compile it
        # FIXME(skullydazed): add code to check and warn if the keymap already exists when compiling a json keymap.
        user_keymap = parse_configurator_json(cli.args.filename)
        command = compile_configurator_json(user_keymap)

    else:
        if cli.config.compile.keyboard and cli.config.compile.keymap:
            # Generate the make command for a specific keyboard/keymap.
            command = create_make_command(cli.config.compile.keyboard, cli.config.compile.keymap)

        elif not cli.config.compile.keyboard:
            cli.log.error('Could not determine keyboard!')
        elif not cli.config.compile.keymap:
            cli.log.error('Could not determine keymap!')

    # Compile the firmware, if we're able to
    if command:
        cli.log.info('Compiling keymap with {fg_cyan}%s', ' '.join(command))
        if not cli.args.dry_run:
            cli.echo('\n')
            compile = subprocess.run(command)
            return compile.returncode

    else:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.echo('usage: qmk compile [-h] [-b] [-kb KEYBOARD] [-km KEYMAP] [filename]')
        return False
