"""Format files according to QMK's style.
"""
from milc import cli

import subprocess

from qmk.path import normpath

from itertools import islice


def _get_chunks(it, size):
    it = iter(it)
    return iter(lambda: tuple(islice(it, size)), ())


def dos2unix_run(files):
    """Spawn multiple dos2unix subprocess avoiding too long commands on formatting everything
    """
    for chunk in _get_chunks(files, 10):
        dos2unix = subprocess.run(['dos2unix', *chunk])

        if dos2unix.returncode:
            return False


@cli.argument('-a', '--all-files', arg_only=True, action='store_true', help='Format all core files.')
@cli.argument('-b', '--base-branch', default='origin/master', help='Branch to compare to diffs to.')
@cli.argument('files', nargs='*', arg_only=True, help='Filename(s) to format.')
@cli.subcommand("Format files according to QMK's style.", hidden=True)
def fileformat(cli):
    """Run several general formatting commands.
    """
    files = []

    # Find the list of files to format
    if cli.args.files:
        files.extend(normpath(file) for file in cli.args.files)
        if cli.args.all_files:
            cli.log.warning('Filenames passed with -a, only formatting: %s', ','.join(map(str, files)))
    # If -a is specified
    elif cli.args.all_files:
        ls_args = ['git', 'ls-files']
        out = subprocess.run(ls_args, check=True, stdout=subprocess.PIPE)
        files = filter(None, out.stdout.decode('UTF-8').split('\n'))
    # No files specified & no -a flag
    else:
        base_args = ['git', 'diff', '--name-only', cli.args.base_branch]
        out = subprocess.run(base_args, check=True, stdout=subprocess.PIPE)
        files = filter(None, out.stdout.decode('UTF-8').split('\n'))

    return dos2unix_run(files)
