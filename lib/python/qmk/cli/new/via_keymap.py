"""This script creates a starting point for a keyboard's VIA support.
"""

from qmk.path import is_keyboard
import qmk.keymap
from qmk.errors import KeymapAlreadyExistsError

from milc import cli


@cli.argument('-kb', '--keyboard', required=True, help='Specify keyboard name. Example: 1upkeyboards/1up60hse')
@cli.subcommand('Creates a new VIA keymap for the keyboard of your choosing')
def via_keymap(cli):
    if is_keyboard(cli.config.via_keymap.keyboard):
        try:
            qmk.keymap.via_keymap(cli.config.via_keymap.keyboard)
        except KeymapAlreadyExistsError as e:
            cli.log.error(e)
    else:
        cli.log.error('%s is not a valid QMK keyboard.', cli.config.via_keymap.keyboard)
