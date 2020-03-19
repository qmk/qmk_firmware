""" List the keymaps for a specific keyboard
"""

import qmk.keymap
from milc import cli
from qmk.errors import NoSuchKeyboardError
from qmk.decorators import automagic_keyboard


@cli.argument('-kb', '--keyboard', help='Specify the keyboard. Example: 1upkeyboards/1up60hse')
@cli.subcommand('List the keymaps for a specific keyboard')
@automagic_keyboard
def list_keymaps(cli):
    """List the keymaps for a specific keyboard
    """

    # Prompt the user for a keyboard
    while not cli.config.list_keymaps.keyboard:
        cli.echo('Specify the keyboard. Example: 1upkeyboards/1up60hse\n')
        cli.config.list_keymaps.keyboard = input('Keyboard: ')

    try:
        for name in qmk.keymap.list_keymaps(cli.config.list_keymaps.keyboard):
            # echo instead of config.log.info for easier output piping
            cli.echo('%s', name)
    except (FileNotFoundError, PermissionError) as e:
        cli.echo('{fg_red}%s: %s', cli.config.list_keymaps.keyboard, e)
