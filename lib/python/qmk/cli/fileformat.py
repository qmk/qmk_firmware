"""Format files according to QMK's style.
"""
from milc import cli

import subprocess


@cli.subcommand("Format files according to QMK's style.", hidden=True)
def fileformat(cli):
    """Run several general formatting commands.
    """
    dos2unix = subprocess.run(['bash', '-c', 'dos2unix **'])
    return dos2unix.returncode
