"""QMK Subcommand List
"""
from milc import cli
from qmk.path import subcommand_modules


@cli.subcommand('QMK Subcommand List.')
def subcommands(cli):
    """Output a list of subcommands separated by '\n'.
    """
    for subcommand_module in sorted(subcommand_modules()):
        print('-'.join(subcommand_module.split('.')[2:]))
