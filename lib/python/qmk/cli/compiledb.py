"""Creates a compilation database for the given keyboard build.
"""
import subprocess
from argparse import FileType

from milc import cli

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import create_make_command
from qmk.build_log_parse import parse_make_n
from qmk.constants import QMK_FIRMWARE
import json


@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.subcommand('Create a compilation database.')
@automagic_keyboard
@automagic_keymap
def compile(cli):
    """Creates a compilation database for the given keyboard build.

    Does a make clean, then a make -n for this target and uses the dry-run output to create
    a compilation database (compile_commands.json). This file can help some IDEs and
    IDE-like editors work better. For more information about this:

        https://clang.llvm.org/docs/JSONCompilationDatabase.html
    """
    command = None

    if cli.config.compile.keyboard and cli.config.compile.keymap:
        # Generate the make command for a specific keyboard/keymap.
        command = create_make_command(cli.config.compile.keyboard, cli.config.compile.keymap, dry_run=True)

    elif not cli.config.compile.keyboard:
        cli.log.error('Could not determine keyboard!')
    elif not cli.config.compile.keymap:
        cli.log.error('Could not determine keymap!')

    if command:
        cli.log.info('Making clean')
        subprocess.run(['make', 'clean'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

        cli.log.info('Gathering build instructions')
        proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        db = parse_make_n(proc.stdout)
        res = proc.wait()
        if res != 0:
            raise RuntimeError(f"Got error from: {repr(command)}")

        cli.log.info(f"Found {len(db)} compile commands")

        dbpath = QMK_FIRMWARE / 'compile_commands.json'

        cli.log.info(f"Writing build database to {dbpath}")
        dbpath.write_text(json.dumps(db, indent=4))

    else:
        cli.log.error('You must supply both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.echo('usage: qmk compiledb [-kb KEYBOARD] [-km KEYMAP]')
        return False
