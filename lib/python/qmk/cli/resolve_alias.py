from qmk.keyboard import keyboard_folder

from milc import cli


@cli.argument('--allow-unknown', arg_only=True, action='store_true', help="Return original if rule is not a valid keyboard.")
@cli.argument('keyboard', arg_only=True, help='The keyboard\'s name')
@cli.subcommand('Resolve DEFAULT_FOLDER and any keyboard_aliases for provided rule')
def resolve_alias(cli):
    try:
        print(keyboard_folder(cli.args.keyboard))
    except ValueError:
        if cli.args.allow_unknown:
            print(cli.args.keyboard)
        else:
            raise
