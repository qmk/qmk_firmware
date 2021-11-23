"""Format python code according to QMK's style.
"""
from subprocess import CalledProcessError, DEVNULL

from milc import cli

from qmk.path import normpath

py_file_suffixes = ('py',)
py_dirs = ['lib/python']


def yapf_run(files):
    edit = '--diff' if cli.args.dry_run else '--in-place'
    yapf_cmd = ['yapf', '-vv', '--recursive', edit, *files]
    try:
        cli.run(yapf_cmd, check=True, capture_output=False, stdin=DEVNULL)
        cli.log.info('Successfully formatted the python code.')

    except CalledProcessError:
        cli.log.error(f'Python code in {",".join(py_dirs)} incorrectly formatted!')
        return False


def filter_files(files):
    """Yield only files to be formatted and skip the rest
    """
    for file in files:
        if file and normpath(file).name.split('.')[-1] in py_file_suffixes:
            yield file
        else:
            cli.log.debug('Skipping file %s', file)


@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually format.")
@cli.argument('-b', '--base-branch', default='origin/master', help='Branch to compare to diffs to.')
@cli.argument('-a', '--all-files', arg_only=True, action='store_true', help='Format all files.')
@cli.argument('files', nargs='*', arg_only=True, type=normpath, help='Filename(s) to format.')
@cli.subcommand("Format python code according to QMK's style.", hidden=False if cli.config.user.developer else True)
def format_python(cli):
    """Format python code according to QMK's style.
    """
    # Find the list of files to format
    if cli.args.files:
        files = list(filter_files(cli.args.files))

        if not files:
            cli.log.error('No Python files in filelist: %s', ', '.join(map(str, cli.args.files)))
            exit(0)

        if cli.args.all_files:
            cli.log.warning('Filenames passed with -a, only formatting: %s', ','.join(map(str, files)))

    elif cli.args.all_files:
        git_ls_cmd = ['git', 'ls-files', *py_dirs]
        git_ls = cli.run(git_ls_cmd, stdin=DEVNULL)
        files = list(filter_files(git_ls.stdout.split('\n')))

    else:
        git_diff_cmd = ['git', 'diff', '--name-only', cli.args.base_branch, *py_dirs]
        git_diff = cli.run(git_diff_cmd, stdin=DEVNULL)
        files = list(filter_files(git_diff.stdout.split('\n')))

    # Sanity check
    if not files:
        cli.log.error('No changed files detected. Use "qmk format-python -a" to format all files')
        return False

    return yapf_run(files)
