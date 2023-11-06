"""List the keyboards currently defined within QMK
"""
from milc import cli

import qmk.keyboard


@cli.argument('--no-resolve-defaults', arg_only=True, action='store_false', help='Ignore any "DEFAULT_FOLDER" within keyboards rules.mk')
@cli.subcommand("List the keyboards currently defined within QMK")
def list_keyboards(cli):
    """List the keyboards currently defined within QMK
    """
    for keyboard_name in qmk.keyboard.list_keyboards(cli.args.no_resolve_defaults):
        print(keyboard_name)
