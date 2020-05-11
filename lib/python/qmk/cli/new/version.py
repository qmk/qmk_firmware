"""Increment the QMK version.
"""
from milc import cli


@cli.argument('-n', '--dry-run', help='Show what changes will be made but do not make them.')
@cli.subcommand('Increment the QMK version.', hidden=False if cli.config.user.developer else True)
def new_version(cli):
    """Increment the QMK version.
    """
    cli.log.info('Hello!')
