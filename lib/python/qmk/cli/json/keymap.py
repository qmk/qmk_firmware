"""Generate a keymap.c from a configurator export.
"""
import json
from pathlib import Path

from milc import cli

import qmk.keymap
import qmk.path


@cli.argument('-o', '--output', arg_only=True, type=Path, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', arg_only=True, help='Configurator JSON file')
@cli.subcommand('Creates a keymap.c from a QMK Configurator export.')
def json_keymap(cli):
    """Generate a keymap.c from a configurator export.

    This command uses the `qmk.keymap` module to generate a keymap.c from a configurator export. The generated keymap is written to stdout, or to a file if -o is provided.
    """
    cli.log.error('This command has been renamed to `qmk json2c`.')
    exit(1)
