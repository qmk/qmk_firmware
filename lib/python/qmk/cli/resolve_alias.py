from qmk.keyboard import keyboard_folder

from milc import cli

@cli.argument('keyboard', arg_only=True, help='TODO.')
@cli.subcommand('TODO')
def resolve_alias(cli):
    print(keyboard_folder(cli.args.keyboard))
