"""Creates a compilation database for the given keyboard build.
"""

import json
import os
import re
import shlex
import shutil
from functools import lru_cache
from pathlib import Path
from typing import Dict, Iterator, List, Union

from milc import cli, MILC

from qmk.commands import create_make_command
from qmk.constants import QMK_FIRMWARE
from qmk.decorators import automagic_keyboard, automagic_keymap


@lru_cache(maxsize=10)
def system_libs(binary: str) -> List[Path]:
    """Find the system include directory that the given build tool uses.
    """
    cli.log.debug("searching for system library directory for binary: %s", binary)
    bin_path = shutil.which(binary)

    # Actually query xxxxxx-gcc to find its include paths.
    if binary.endswith("gcc") or binary.endswith("g++"):
        result = cli.run([binary, '-E', '-Wp,-v', '-'], capture_output=True, check=True, input='\n')
        paths = []
        for line in result.stderr.splitlines():
            if line.startswith(" "):
                paths.append(Path(line.strip()).resolve())
        return paths

    return list(Path(bin_path).resolve().parent.parent.glob("*/include")) if bin_path else []


file_re = re.compile(r'printf "Compiling: ([^"]+)')
cmd_re = re.compile(r'LOG=\$\((.+?)&&')


def parse_make_n(f: Iterator[str]) -> List[Dict[str, str]]:
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
            assert this_file
            m = cmd_re.search(line)
            if m:
                # we have a hit!
                this_cmd = m.group(1)
                args = shlex.split(this_cmd)
                for s in system_libs(args[0]):
                    args += ['-isystem', '%s' % s]
                new_cmd = ' '.join(shlex.quote(s) for s in args if s != '-mno-thumb-interwork')
                records.append({"directory": str(QMK_FIRMWARE.resolve()), "command": new_cmd, "file": this_file})
                state = 'start'

    return records


@cli.argument('-kb', '--keyboard', help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.subcommand('Create a compilation database.')
@automagic_keyboard
@automagic_keymap
def generate_compilation_database(cli: MILC) -> Union[bool, int]:
    """Creates a compilation database for the given keyboard build.

    Does a make clean, then a make -n for this target and uses the dry-run output to create
    a compilation database (compile_commands.json). This file can help some IDEs and
    IDE-like editors work better. For more information about this:

        https://clang.llvm.org/docs/JSONCompilationDatabase.html
    """
    command = None
    # check both config domains: the magic decorator fills in `generate_compilation_database` but the user is
    # more likely to have set `compile` in their config file.
    current_keyboard = cli.config.generate_compilation_database.keyboard or cli.config.user.keyboard
    current_keymap = cli.config.generate_compilation_database.keymap or cli.config.user.keymap

    if current_keyboard and current_keymap:
        # Generate the make command for a specific keyboard/keymap.
        command = create_make_command(current_keyboard, current_keymap, dry_run=True)
    elif not current_keyboard:
        cli.log.error('Could not determine keyboard!')
    elif not current_keymap:
        cli.log.error('Could not determine keymap!')

    if not command:
        cli.log.error('You must supply both `--keyboard` and `--keymap`, or be in a directory for a keyboard or keymap.')
        cli.echo('usage: qmk compiledb [-kb KEYBOARD] [-km KEYMAP]')
        return False

    # remove any environment variable overrides which could trip us up
    env = os.environ.copy()
    env.pop("MAKEFLAGS", None)

    # re-use same executable as the main make invocation (might be gmake)
    clean_command = [command[0], 'clean']
    cli.log.info('Making clean with {fg_cyan}%s', ' '.join(clean_command))
    cli.run(clean_command, capture_output=False, check=True, env=env)

    cli.log.info('Gathering build instructions from {fg_cyan}%s', ' '.join(command))

    result = cli.run(command, capture_output=True, check=True, env=env)
    db = parse_make_n(result.stdout.splitlines())
    if not db:
        cli.log.error("Failed to parse output from make output:\n%s", result.stdout)
        return False

    cli.log.info("Found %s compile commands", len(db))

    dbpath = QMK_FIRMWARE / 'compile_commands.json'

    cli.log.info(f"Writing build database to {dbpath}")
    dbpath.write_text(json.dumps(db, indent=4))

    return True
