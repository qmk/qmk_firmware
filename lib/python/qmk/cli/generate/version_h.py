"""Used by the make system to generate version.h for use in code.
"""
from time import strftime

from milc import cli

from qmk.path import normpath
from qmk.commands import dump_lines
from qmk.git import git_get_qmk_hash, git_get_qmk_major_minor_patch, git_get_version, git_is_dirty
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
        git_dirty = False
        git_version = "NA"
        git_qmk_hash = "NA"
        chibios_version = "NA"
        chibios_contrib_version = "NA"
        # these variable aren't wrapped on quotes when generating the version file as they are number when git isn't skipped
        # we add double quoting here such that generated code is valid
        qmk_major, qmk_minor, qmk_patch, qmk_global = ['"NA"'] * 4
    else:
        git_dirty = git_is_dirty()
        git_version = git_get_version() or current_time
        git_qmk_hash = git_get_qmk_hash() or "Unknown"
        chibios_version = git_get_version("chibios", "os") or current_time
        chibios_contrib_version = git_get_version("chibios-contrib", "os") or current_time
        qmk_major, qmk_minor, qmk_patch = git_get_qmk_major_minor_patch()
        # number that can be used to order all versions, eg '#if __QMK__ == 000020005' (for 0.20.5)
        # TODO: proper handling when function fails and returns "NA", so int() doesn't error out (?)
        # FIXME: may need to reserve more than 3 digits for each number
        qmk_global = int(f"{qmk_major:03}{qmk_minor:03}{qmk_patch:03}")

    dirty_indicator = "*" if git_dirty else ""

    # Build the version.h file.
    version_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once']

    version_h_lines.extend([
        f'#define QMK_VERSION "{git_version}"',
        f'#define QMK_MAJOR {qmk_major}',
        f'#define QMK_MINOR {qmk_minor}',
        f'#define QMK_PATCH {qmk_patch}',
        f'#define __QMK__ {qmk_global}',
        f'#define QMK_BUILDDATE "{current_time}"',
        f'#define QMK_GIT_HASH  "{git_qmk_hash}{dirty_indicator}"',
        f'#define CHIBIOS_VERSION "{chibios_version}"',
        f'#define CHIBIOS_CONTRIB_VERSION "{chibios_contrib_version}"',
    ])

    # Show the results
    dump_lines(cli.args.output, version_h_lines, cli.args.quiet)
