"""Ensure text files have the proper line endings.
"""
from itertools import islice
from subprocess import DEVNULL

from milc import cli

from qmk.path import normpath


def _get_chunks(it, size):
    """Break down a collection into smaller parts
    """
    it = iter(it)
    return iter(lambda: tuple(islice(it, size)), ())


def dos2unix_run(files):
    """Spawn multiple dos2unix subprocess avoiding too long commands on formatting everything
    """
    for chunk in _get_chunks(files, 10):
        dos2unix = cli.run(['dos2unix', *chunk])

        if dos2unix.returncode:
            return False


@cli.argument('-b', '--base-branch', default='origin/master', help='Branch to compare to diffs to.')
@cli.argument('-a', '--all-files', arg_only=True, action='store_true', help='Format all files.')
@cli.argument('files', nargs='*', arg_only=True, type=normpath, help='Filename(s) to format.')
@cli.subcommand("Ensure text files have the proper line endings.", hidden=True)
def format_text(cli):
    """Ensure text files have the proper line endings.
    """
    # Find the list of files to format
    if cli.args.files:
        files = list(cli.args.files)

        if cli.args.all_files:
            cli.log.warning('Filenames passed with -a, only formatting: %s', ','.join(map(str, files)))

    elif cli.args.all_files:
        git_ls_cmd = ['git', 'ls-files']
        git_ls = cli.run(git_ls_cmd, stdin=DEVNULL)
        files = list(filter(None, git_ls.stdout.split('\n')))

    else:
        git_diff_cmd = ['git', 'diff', '--name-only', cli.args.base_branch]
        git_diff = cli.run(git_diff_cmd, stdin=DEVNULL)
        files = list(filter(None, git_diff.stdout.split('\n')))

    # Sanity check
    if not files:
        cli.log.error('No changed files detected. Use "qmk format-text -a" to format all files')
        return False

    return dos2unix_run(files)
