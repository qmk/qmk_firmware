"""Used by the make system to generate version.h for use in code.
"""
from time import strftime

from milc import cli

from qmk.path import normpath
from qmk.commands import dump_lines
from qmk.git import git_get_qmk_hash, git_get_version, git_is_dirty
from qmk.constants import GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE

TIME_FMT = '%Y-%m-%d-%H:%M:%S'
QMK_VERSION_FILE = 'qmk_version.h'


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
    else:
        git_dirty = git_is_dirty()
        git_version = git_get_version() or current_time
        git_qmk_hash = git_get_qmk_hash() or "Unknown"
        chibios_version = git_get_version("chibios", "os") or current_time
        chibios_contrib_version = git_get_version("chibios-contrib", "os") or current_time

    dirty_indicator = "*" if git_dirty else ""

    # yapf: disable
    if (
        git_version in (
            "NA",  # git skipped
            current_time,  # git command failed
        ) or "." not in git_version  # no tag in git
    ):
        # yapf: enable
        error = 'PRAGMA(GCC error "Cant check QMK version under current settings")'
        fallback_versions = [
            f'#    define QMK_MAJOR {error}',
            f'#    define QMK_MINOR {error}',
            f'#    define QMK_PATCH {error}',
            f'#    define __QMK__ {error}',
        ]
    else:
        versions = git_version.split("-")[0]
        qmk_major, qmk_minor, qmk_patch = map(int, versions.split("."))
        fallback_versions = [
            f'#    define QMK_MAJOR {qmk_major}',
            f'#    define QMK_MINOR {qmk_minor}',
            f'#    define QMK_PATCH {qmk_patch}',
            f'#    define __QMK__ 0x{qmk_major:02}{qmk_minor:03}{qmk_patch:03}',
        ]

    # Build the version.h file.
    version_h_lines = [GPL2_HEADER_C_LIKE, GENERATED_HEADER_C_LIKE, '#pragma once']

    version_h_lines.extend([
        '',
        '// added in late 2023, need to check whether it exists',
        f'#if __has_include("{QMK_VERSION_FILE}")',
        f'#    include "{QMK_VERSION_FILE}"',
        '#else // extract info from git tags as fallback',
        *fallback_versions,
        '#endif // __has_include'
        '',
        f'#define QMK_VERSION "{git_version}"',
        f'#define QMK_BUILDDATE "{current_time}"',
        f'#define QMK_GIT_HASH  "{git_qmk_hash}{dirty_indicator}"',
        f'#define CHIBIOS_VERSION "{chibios_version}"',
        f'#define CHIBIOS_CONTRIB_VERSION "{chibios_contrib_version}"',
    ])

    # Show the results
    dump_lines(cli.args.output, version_h_lines, cli.args.quiet)
