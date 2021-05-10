"""Format python code according to QMK's style.
"""
import subprocess

from milc import cli

from qmk.path import normpath

py_dirs = ['bin/qmk', 'lib/python']


def yapf_run(files):
    try:
        subprocess.run(['yapf', '-vv', '-ri', *files], check=True)
        cli.log.info('Successfully formatted the python code.')

    except subprocess.CalledProcessError:
        cli.log.error('Error formatting python code!')
        return False


@cli.argument('-a', '--all-files', arg_only=True, action='store_true', help='Format all core files.')
@cli.argument('-b', '--base-branch', default='origin/master', help='Branch to compare to diffs to.')
@cli.argument('files', nargs='*', arg_only=True, help='Filename(s) to format.')
@cli.subcommand("Format python code according to QMK's style.", hidden=False if cli.config.user.developer else True)
def pyformat(cli):
    """Format python code according to QMK's style.
    """

    files = []

    # Find the list of files to format
    if cli.args.files:
        files.extend(normpath(file) for file in cli.args.files)
        if cli.args.all_files:
            cli.log.warning('Filenames passed with -a, only formatting: %s', ','.join(map(str, files)))
    # If -a is specified
    elif cli.args.all_files:
        files = py_dirs
    # No files specified & no -a flag
    else:
        base_args = ['git', 'diff', '--name-only', cli.args.base_branch]
        out = subprocess.run(base_args + py_dirs, check=True, stdout=subprocess.PIPE)
        files = filter(None, out.stdout.decode('UTF-8').split('\n'))

    return yapf_run(files)
