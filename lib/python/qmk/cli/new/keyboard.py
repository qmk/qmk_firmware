"""This script automates the creation of keyboards.
"""
from subprocess import DEVNULL

from milc import cli


@cli.subcommand('Creates a new keyboard')
def new_keyboard(cli):
    """Creates a new keyboard
    """
    # TODO: replace this bodge to the existing script
    cli.run(['util/new_keyboard.sh'], stdin=DEVNULL, capture_output=False)
