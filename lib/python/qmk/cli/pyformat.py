"""Format python code according to QMK's style.
"""
from milc import cli

import subprocess


@cli.entrypoint("Format python code according to QMK's style.")
def main(cli):
    """Format python code according to QMK's style.
    """
    try:
        subprocess.run(['yapf', '-vv', '-ri', 'bin/qmk', 'lib/python'], check=True)
        cli.log.info('Successfully formatted the python code in `bin/qmk` and `lib/python`.')
    except subprocess.CalledProcessError:
        cli.log.error('Error formatting python code!')
