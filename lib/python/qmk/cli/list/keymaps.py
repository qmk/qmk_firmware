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
    try:
        for name in qmk.keymap.list_keymaps(cli.config.list_keymaps.keyboard):
            # We echo instead of cli.log.info to allow easier piping of this output
            cli.echo('%s', name)
    except NoSuchKeyboardError as e:
        cli.echo("{fg_red}%s: %s", cli.config.list_keymaps.keyboard, e.message)
    except (FileNotFoundError, PermissionError) as e:
        cli.echo("{fg_red}%s: %s", cli.config.list_keymaps.keyboard, e)
    except TypeError:
        cli.echo("{fg_red}Something went wrong. Did you specify a keyboard?")
