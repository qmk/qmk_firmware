""" List the keymaps for a specific keyboard
"""

import qmk.keymap
from milc import cli
from qmk.errors import NoSuchKeyboardError


@cli.argument('-kb', '--keyboard', help='Specify the keyboard. Example: 1upkeyboards//1up60hse')
@cli.subcommand('List the keymaps for a specific keyboard')
def list_keymaps(cli):
    """List the keymaps for a specific keyboard
    """

    # Prompt the user for a keyboard
    while not cli.args.keyboard:
        cli.args.keyboard = input('Specifiy the keyboard. Example: 1upkeyboards/1up60hse\n')

    try:
        for name in qmk.keymap.list_keymaps(cli.args.keyboard):
            # echo instead of config.log.info for easier output piping
            cli.echo('%s:%s', cli.args.keyboard, name)
    except NoSuchKeyboardError as e:
        cli.echo('{fg_red}%s: %s', cli.args.keyboard, e.message)
    except (FileNotFoundError, PermissionError) as e:
        cli.echo('{fg_red}%s: %s', cli.args.keyboard, e)
