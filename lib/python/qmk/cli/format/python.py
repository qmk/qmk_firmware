"""Format python code according to QMK's style.
"""
from subprocess import CalledProcessError, DEVNULL

from milc import cli


@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually format.")
@cli.subcommand("Format python code according to QMK's style.", hidden=False if cli.config.user.developer else True)
def format_python(cli):
    """Format python code according to QMK's style.
    """
    edit = '--diff' if cli.args.dry_run else '--in-place'
    yapf_cmd = ['yapf', '-vv', '--recursive', edit, 'bin/qmk', 'lib/python']
    try:
        cli.run(yapf_cmd, check=True, capture_output=False, stdin=DEVNULL)
        cli.log.info('Python code in `bin/qmk` and `lib/python` is correctly formatted.')
        return True

    except CalledProcessError:
        if cli.args.dry_run:
            cli.log.error('Python code in `bin/qmk` and `lib/python` incorrectly formatted!')
        else:
            cli.log.error('Error formatting python code!')

    return False
