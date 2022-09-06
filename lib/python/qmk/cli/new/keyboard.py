"""This script automates the creation of keyboards.
"""
from milc import cli


@cli.subcommand('Creates a new keyboard')
def new_keyboard(cli):
    """Creates a new keyboard
    """
    # TODO: replace this bodge to the existing script
    cli.run(['util/new_keyboard.sh'], stdin=None, capture_output=False)
