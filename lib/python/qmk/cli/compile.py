"""Compile a QMK Firmware.

You can compile a keymap already in the repo or using a QMK Configurator export.
"""
import subprocess
from argparse import FileType

from milc import cli

import qmk.path
from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.commands import compile_configurator_json, create_make_command, parse_configurator_json
from qmk.compile_commands_json import parse_make_n, qmk_dir
from pathlib import Path
import json


@cli.argument('filename', nargs='?', arg_only=True, type=FileType('r'), help='The configurator export to compile')
@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the make command to be run.")
@cli.argument('-b', '--builddb', arg_only=True, action='store_true',
              help="Does a make clean, then a make -n for this target and uses the dry-run output to create "
              "a compilation database (compile_commands.json). This file can help some IDEs and "
              "IDE-like editors work better. For more information about this: "
              "https://clang.llvm.org/docs/JSONCompilationDatabase.html")
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
        keymap_path = qmk.path.keymap(user_keymap['keyboard'])
        command = compile_configurator_json(user_keymap)

        cli.log.info('Wrote keymap to {fg_cyan}%s/%s/keymap.c', keymap_path, user_keymap['keymap'])

    else:
        if cli.config.compile.keyboard and cli.config.compile.keymap:
            # Generate the make command for a specific keyboard/keymap.
            dry_run = cli.args.builddb
            command = create_make_command(cli.config.compile.keyboard, cli.config.compile.keymap, dry_run=dry_run)

        elif not cli.config.compile.keyboard:
            cli.log.error('Could not determine keyboard!')
        elif not cli.config.compile.keymap:
            cli.log.error('Could not determine keymap!')

    if command:
        if cli.args.builddb:
            cli.log.info('Making clean')
            subprocess.run(['make', 'clean'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

            cli.log.info('Gathering build instructions')
            proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            db = parse_make_n(proc.stdout)
            res = proc.wait()
            if res != 0:
                raise RuntimeError(f"Got error from: {repr(command)}")

            cli.log.info(f"Found {len(db)} compile commands")

            dbpath = qmk_dir / 'compile_commands.json'

            cli.log.info(f"Writing build database to {dbpath}")
            dbpath.write_text(json.dumps(db, indent=4))

        else:
            # Compile the firmware, if we're able to
            cli.log.info('Compiling keymap with {fg_cyan}%s', ' '.join(command))
            if not cli.args.dry_run:
                cli.echo('\n')
                subprocess.run(command)

    else:
        cli.log.error('You must supply a configurator export, both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.echo('usage: qmk compile [-h] [-b] [-kb KEYBOARD] [-km KEYMAP] [filename]')
        return False
