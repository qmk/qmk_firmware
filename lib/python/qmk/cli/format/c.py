"""Format C code according to QMK's style.
"""
from shutil import which
from subprocess import CalledProcessError, DEVNULL, Popen, PIPE

from argcomplete.completers import FilesCompleter
from milc import cli

from qmk.path import normpath
from qmk.c_parse import c_source_files

c_file_suffixes = ('c', 'h', 'cpp', 'hpp')
core_dirs = ('drivers', 'quantum', 'tests', 'tmk_core', 'platforms')
ignored = ('tmk_core/protocol/usb_hid', 'platforms/chibios/boards')


def is_relative_to(file, other):
    """Provide similar behavior to PurePath.is_relative_to in Python > 3.9
    """
    return str(normpath(file).resolve()).startswith(str(normpath(other).resolve()))


def find_clang_format():
    """Returns the path to clang-format.
    """
    for clang_version in range(20, 6, -1):
        binary = f'clang-format-{clang_version}'

        if which(binary):
            return binary

    return 'clang-format'


def find_diffs(files):
    """Run clang-format and diff it against a file.
    """
    found_diffs = False

    for file in files:
        cli.log.debug('Checking for changes in %s', file)
        clang_format = Popen([find_clang_format(), file], stdout=PIPE, stderr=PIPE, universal_newlines=True)
        diff = cli.run(['diff', '-u', f'--label=a/{file}', f'--label=b/{file}', str(file), '-'], stdin=clang_format.stdout, capture_output=True)

        if diff.returncode != 0:
            print(diff.stdout)
            found_diffs = True

    return found_diffs


def cformat_run(files):
    """Spawn clang-format subprocess with proper arguments
    """
    # Determine which version of clang-format to use
    clang_format = [find_clang_format(), '-i']

    try:
        cli.run([*clang_format, *map(str, files)], check=True, capture_output=False, stdin=DEVNULL)
        cli.log.info('Successfully formatted the C code.')
        return True

    except CalledProcessError as e:
        cli.log.error('Error formatting C code!')
        cli.log.debug('%s exited with returncode %s', e.cmd, e.returncode)
        cli.log.debug('STDOUT:')
        cli.log.debug(e.stdout)
        cli.log.debug('STDERR:')
        cli.log.debug(e.stderr)
        return False


def filter_files(files, core_only=False):
    """Yield only files to be formatted and skip the rest
    """
    files = list(map(normpath, filter(None, files)))

    for file in files:
        if core_only:
            # The following statement checks each file to see if the file path is
            # - in the core directories
            # - not in the ignored directories
            if not any(is_relative_to(file, i) for i in core_dirs) or any(is_relative_to(file, i) for i in ignored):
                cli.log.debug("Skipping non-core file %s, as '--core-only' is used.", file)
                continue

        if file.suffix[1:] in c_file_suffixes:
            yield file
        else:
            cli.log.debug('Skipping file %s', file)


@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Flag only, don't automatically format.")
@cli.argument('-b', '--base-branch', default='origin/master', help='Branch to compare to diffs to.')
@cli.argument('-a', '--all-files', arg_only=True, action='store_true', help='Format all core files.')
@cli.argument('--core-only', arg_only=True, action='store_true', help='Format core files only.')
@cli.argument('files', nargs='*', arg_only=True, type=normpath, completer=FilesCompleter('.c'), help='Filename(s) to format.')
@cli.subcommand("Format C code according to QMK's style.", hidden=False if cli.config.user.developer else True)
def format_c(cli):
    """Format C code according to QMK's style.
    """
    # Find the list of files to format
    if cli.args.files:
        files = list(filter_files(cli.args.files, cli.args.core_only))

        if not files:
            cli.log.error('No C files in filelist: %s', ', '.join(map(str, cli.args.files)))
            exit(0)

        if cli.args.all_files:
            cli.log.warning('Filenames passed with -a, only formatting: %s', ','.join(map(str, files)))

    elif cli.args.all_files:
        all_files = c_source_files(core_dirs)
        files = list(filter_files(all_files, True))

    else:
        git_diff_cmd = ['git', 'diff', '--name-only', cli.args.base_branch, *core_dirs]
        git_diff = cli.run(git_diff_cmd, stdin=DEVNULL)

        if git_diff.returncode != 0:
            cli.log.error("Error running %s", git_diff_cmd)
            print(git_diff.stderr)
            return git_diff.returncode

        changed_files = git_diff.stdout.strip().split('\n')
        files = list(filter_files(changed_files, True))

    # Sanity check
    if not files:
        cli.log.error('No changed files detected. Use "qmk format-c -a" to format all core files')
        return False

    # Run clang-format on the files we've found
    if cli.args.dry_run:
        return not find_diffs(files)
    else:
        return cformat_run(files)
