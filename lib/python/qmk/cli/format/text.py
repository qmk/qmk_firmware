"""Ensure text files have the proper line endings.
"""
from itertools import islice
from subprocess import DEVNULL

from milc import cli

from qmk.path import normpath, is_relative_to

IGNORE_SUFFIXES = [
    'hex',
    'ico',
    'jpeg',
    'jpg',
    'png',
]
IGNORE_DIRS = [
    'lib/fnv',
    'lib/lib8tion',
    'lib/usbhost',
]


def _get_chunks(it, size):
    """Break down a collection into smaller parts
    """
    it = iter(it)
    return iter(lambda: tuple(islice(it, size)), ())


def _check_dos2unix():
    """Check for a 'valid' dos2unix executable
    """
    dos2unix = cli.run(['dos2unix', '--help'])
    return dos2unix.returncode == 0 and '--add-eol' in dos2unix.stdout


def dos2unix_run(files):
    """Spawn multiple dos2unix subprocess avoiding too long commands on formatting everything
    """
    for chunk in _get_chunks([normpath(file).as_posix() for file in files], 10):
        dos2unix = cli.run(['dos2unix', '--add-eol', *chunk])

        if dos2unix.returncode:
            cli.log.debug(dos2unix.stdout)
            cli.log.error(dos2unix.stderr)
            return False


def filter_files(files):
    """Yield only files to be formatted and skip the rest
    """
    ret = []

    for file in map(normpath, filter(None, files)):
        if file.suffix[1:] in IGNORE_SUFFIXES:
            continue

        if not any(is_relative_to(file, i) for i in IGNORE_DIRS):
            ret.append(file)

    return ret


@cli.argument('-b', '--base-branch', default='origin/master', help='Branch to compare to diffs to.')
@cli.argument('-a', '--all-files', arg_only=True, action='store_true', help='Format all files.')
@cli.argument('files', nargs='*', arg_only=True, type=normpath, help='Filename(s) to format.')
@cli.subcommand("Ensure text files have the proper line endings.", hidden=True)
def format_text(cli):
    """Ensure text files have the proper line endings.
    """
    if not _check_dos2unix():
        cli.log.error('Formatting requires an up-to-date version of "dos2unix"')
        return False

    # Find the list of files to format
    if cli.args.files:
        files = filter_files(cli.args.files)

        if not files:
            cli.log.error('No valid files in filelist: %s', ', '.join(map(str, cli.args.files)))
            return False

        if cli.args.all_files:
            cli.log.warning('Filenames passed with -a, only formatting: %s', ','.join(map(str, files)))

    elif cli.args.all_files:
        git_ls_cmd = ['git', 'ls-files']
        git_ls = cli.run(git_ls_cmd, stdin=DEVNULL)
        files = filter_files(git_ls.stdout.split('\n'))

    else:
        git_diff_cmd = ['git', 'diff', '--name-only', cli.args.base_branch]
        git_diff = cli.run(git_diff_cmd, stdin=DEVNULL)
        files = filter_files(git_diff.stdout.split('\n'))

    # Sanity check
    if not files:
        cli.log.error('No changed files detected. Use "qmk format-text -a" to format all files')
        return False

    return dos2unix_run(files)
