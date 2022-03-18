"""Used by the make system to generate version.h for use in code.
"""
from time import strftime

from milc import cli

from qmk.path import normpath
from qmk.commands import dump_lines
from qmk.commands import get_git_version
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE

TIME_FMT = '%Y-%m-%d-%H:%M:%S'


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

    if cli.args.skip_all:
        current_time = "1970-01-01-00:00:00"
    else:
        current_time = strftime(TIME_FMT)

    if cli.args.skip_git:
        git_version = "NA"
        chibios_version = "NA"
        chibios_contrib_version = "NA"
    else:
        git_version = get_git_version(current_time)
        chibios_version = get_git_version(current_time, "chibios", "os")
        chibios_contrib_version = get_git_version(current_time, "chibios-contrib", "os")

    # Build the version.h file.
    version_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once']

    version_h_lines.append(f"""
#define QMK_VERSION "{git_version}"
#define QMK_BUILDDATE "{current_time}"
#define CHIBIOS_VERSION "{chibios_version}"
#define CHIBIOS_CONTRIB_VERSION "{chibios_contrib_version}"
""")

    # Show the results
    dump_lines(cli.args.output, version_h_lines, cli.args.quiet)
