"""Creates a compilation database for the given keyboard build.
"""

import json
import re
import shlex
import subprocess
import sys
from argparse import FileType
from functools import lru_cache
from pathlib import Path
from subprocess import check_output
from typing import Dict, List, TextIO

from milc import cli
from qmk.commands import create_make_command
from qmk.constants import QMK_FIRMWARE
from qmk.decorators import automagic_keyboard, automagic_keymap


@lru_cache(maxsize=10)
def system_libs(binary: str):
    """Find the system include directory that the given build tool uses.

    Only tested on OSX+homebrew so far.
    """

    try:
        return list(Path(check_output(['which', binary]).rstrip().decode()).resolve().parent.parent.glob("*/include"))
    except Exception:
        return []


file_re = re.compile(r"""printf "Compiling: ([^"]+)""")
cmd_re = re.compile(r"""LOG=\$\((.+?)\&\&""")


def parse_make_n(f: TextIO) -> List[Dict[str, str]]:
    """parse the output of `make -n <target>`

    This function makes many assumptions about the format of your build log.
    This happens to work right now for qmk.
    """

    state = 'start'
    this_file = None
    records = []
    for line in f:
        if state == 'start':
            m = file_re.search(line)
            if m:
                this_file = m.group(1)
                state = 'cmd'

        if state == 'cmd':
            m = cmd_re.search(line)
            if m:
                # we have a hit!
                this_cmd = m.group(1)
                args = shlex.split(this_cmd)
                args += ['-I%s' % s for s in system_libs(args[0])]
                new_cmd = ' '.join(shlex.quote(s) for s in args if s != '-mno-thumb-interwork')
                records.append({"directory": str(QMK_FIRMWARE.resolve()), "command": new_cmd, "file": this_file})
                state = 'start'

    return records

@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.subcommand('Create a compilation database.')
@automagic_keyboard
@automagic_keymap
def compiledb(cli):
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
