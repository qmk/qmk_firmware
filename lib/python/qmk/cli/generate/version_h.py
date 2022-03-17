"""Used by the make system to generate version.h for use in code.
"""
from milc import cli

from qmk.commands import create_version_h
from qmk.commands import dump_lines
from qmk.path import normpath


@cli.argument('-o', '--output', arg_only=True, type=normpath, help='File to write to')
@cli.argument('-q', '--quiet', arg_only=True, action='store_true', help="Quiet mode, only output error messages")
@cli.argument('--skip-git', arg_only=True, action='store_true', help='Skip Git operations')
@cli.argument('--skip-all', arg_only=True, action='store_true', help='Use placeholder values for all defines (implies --skip-git)')
@cli.subcommand('Used by the make system to generate version.h for use in code', hidden=True)
def generate_version_h(cli):
    """Generates the version.h file.
    """
    if cli.args.skip_all:
        cli.args.skip_git = True

    version_h = create_version_h(cli.args.skip_git, cli.args.skip_all)

    # Show the results
    dump_lines(cli.args.output, version_h.split('\n'), cli.args.quiet)
