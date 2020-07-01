"""Generate a keymap.c from a configurator export.
"""
from pathlib import Path

from milc import cli


@cli.argument('-o', '--output', arg_only=True, type=Path, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('filename', arg_only=True, help='Configurator JSON file')
@cli.subcommand('Creates a keymap.c from a QMK Configurator export.', hidden=True)
def json_keymap(cli):
    """Renamed to `qmk json2c`.
    """
    cli.log.error('This command has been renamed to `qmk json2c`.')
    exit(1)
