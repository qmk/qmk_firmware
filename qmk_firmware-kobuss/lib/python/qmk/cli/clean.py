"""Clean the QMK firmware folder of build artifacts.
"""
from qmk.commands import run
from milc import cli

import shutil


@cli.argument('-a', '--all', arg_only=True, action='store_true', help='Remove *.hex and *.bin files in the QMK root as well.')
@cli.subcommand('Clean the QMK firmware folder of build artifacts.')
def clean(cli):
    """Runs `make clean` (or `make distclean` if --all is passed)
    """
    make_cmd = 'gmake' if shutil.which('gmake') else 'make'

    run([make_cmd, 'distclean' if cli.args.all else 'clean'])
