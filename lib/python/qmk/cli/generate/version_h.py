"""Used by the make system to generate version.h for use in code.
"""
from time import strftime

from milc import cli

from qmk.path import normpath
from qmk.commands import dump_lines
from qmk.git import git_get_qmk_hash, git_get_version, git_is_dirty
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE
from qmk.util import triplet_to_bcd

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
        git_dirty = False
        git_version = "NA"
        git_qmk_hash = "NA"
        git_bcd_version = "0x00000000"
        chibios_version = "NA"
        chibios_contrib_version = "NA"
    else:
        git_dirty = git_is_dirty()
        git_version = git_get_version() or current_time
        git_qmk_hash = git_get_qmk_hash() or "Unknown"
        git_bcd_version = triplet_to_bcd(git_version)
        chibios_version = git_get_version("chibios", "os") or current_time
        chibios_contrib_version = git_get_version("chibios-contrib", "os") or current_time

    # Build the version.h file.
    version_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once']

    version_h_lines.append(
        f"""
#define QMK_VERSION "{git_version}"
#define QMK_BUILDDATE "{current_time}"
#define QMK_VERSION_BCD {git_bcd_version}
#define QMK_GIT_HASH  "{git_qmk_hash}{'*' if git_dirty else ''}"
#define CHIBIOS_VERSION "{chibios_version}"
#define CHIBIOS_CONTRIB_VERSION "{chibios_contrib_version}"
"""
    )

    # Show the results
    dump_lines(cli.args.output, version_h_lines, cli.args.quiet)
