"""Format python code according to QMK's style.
"""
from milc import cli

import subprocess


@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Flag only, don't automatically format.")
@cli.subcommand("Format python code according to QMK's style.", hidden=False if cli.config.user.developer else True)
def pyformat(cli):
    """Format python code according to QMK's style.
    """
    edit = '--diff' if cli.args.dry_run else '--in-place'
    yapf_cmd = ['yapf', '-vv', '--recursive', edit, 'bin/qmk', 'lib/python']
    try:
        cli.run(yapf_cmd, check=True, capture_output=False)
        cli.log.info('Python code in `bin/qmk` and `lib/python` is correctly formatted.')
        return True

    except subprocess.CalledProcessError:
        if cli.args.dry_run:
            cli.log.error('Python code in `bin/qmk` and `lib/python` incorrectly formatted!')
        else:
            cli.log.error('Error formatting python code!')

    return False
