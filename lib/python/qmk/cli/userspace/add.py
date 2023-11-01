from pathlib import Path
from milc import cli

from qmk.constants import QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.keyboard import keyboard_completer, keyboard_folder_or_all
from qmk.keymap import keymap_completer, is_keymap_target
from qmk.userspace import UserspaceDefs


@cli.argument('builds', nargs='*', arg_only=True, help="List of builds in form <keyboard>:<keymap> to compile in parallel. Specifying this overrides all other target search options.")
@cli.argument('-kb', '--keyboard', type=keyboard_folder_or_all, completer=keyboard_completer, help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.subcommand('Adds a build target to userspace `qmk.json`.')
def userspace_add(cli):
    if not HAS_QMK_USERSPACE:
        cli.log.error('Could not determine QMK userspace location. Please run `qmk doctor` or `qmk userspace-doctor` to diagnose.')
        return False

    userspace = UserspaceDefs(QMK_USERSPACE / 'qmk.json')

    if len(cli.args.builds) > 0:
        json_like_targets = list([Path(p) for p in filter(lambda e: Path(e).exists() and Path(e).suffix == '.json', cli.args.builds)])
        make_like_targets = list(filter(lambda e: Path(e) not in json_like_targets, cli.args.builds))

        for e in json_like_targets:
            userspace.add_target(json_path=e)

        for e in make_like_targets:
            s = e.split(':')
            userspace.add_target(keyboard=s[0], keymap=s[1])

    else:
        if not is_keymap_target(cli.args.keyboard, cli.args.keymap):
            cli.log.error('Invalid keymap argument.')
            return False

        userspace.add_target(cli.args.keyboard, cli.args.keymap)

    return userspace.save()
