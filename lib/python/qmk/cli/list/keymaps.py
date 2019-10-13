"""List the keymaps for a specific keyboard
"""
from milc import cli
import qmk.keymap
from qmk.errors import NoSuchKeyboardError

@cli.argument("-kb", "--keyboard", help="Specify keyboard name. Example: 1upkeyboards/1up60hse")
@cli.subcommand("List the keymaps for a specific keyboard")
def list_keymaps(cli):
    """List the keymaps for a specific keyboard
    """
    # ask for user input if keyboard was not provided in the command line
    keyboard_name = cli.config.list_keymaps.keyboard if cli.config.list_keymaps.keyboard else input("Keyboard Name: ")

    try:
        for name in qmk.keymap.list_keymaps(keyboard_name):
            # We echo instead of cli.log.info to allow easier piping of this output
            cli.echo(keyboard_name + ":" + name)
    except NoSuchKeyboardError as e:
        cli.echo("{fg_red}" + e.message)
