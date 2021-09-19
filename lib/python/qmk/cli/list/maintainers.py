"""List the keymaps for a specific keyboard
"""
from pathlib import Path

from milc import cli

from qmk.maintainers import maintainers


@cli.argument("files", type=Path, arg_only=True, nargs='*', help="File to check")
@cli.subcommand("List the maintainers for a file.")
def list_maintainers(cli):
    """List the maintainers for a file.
    """
    for file in cli.args.files:
        cli.echo('%s: %s', file, ', '.join(maintainers(file)))
