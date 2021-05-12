"""Clean the QMK firmware folder of build artifacts.
"""
from qmk.commands import run, create_make_target
from milc import cli


@cli.argument('-a', '--all', arg_only=True, action='store_true', help='Remove *.hex and *.bin files in the QMK root as well.')
@cli.subcommand('Clean the QMK firmware folder of build artifacts.')
def clean(cli):
    """Runs `make clean` (or `make distclean` if --all is passed)
    """
    run(create_make_target('distclean' if cli.args.all else 'clean'))
