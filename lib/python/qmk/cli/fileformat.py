"""Format files according to QMK's style.
"""
from milc import cli

import subprocess


@cli.subcommand("Format files according to QMK's style.", hidden=True)
def fileformat(cli):
    """Run several general formatting commands.
    """
    dos2unix = subprocess.run(['bash', '-c', 'git ls-files -z | xargs -0 dos2unix'], stdout=subprocess.DEVNULL)
    return dos2unix.returncode
