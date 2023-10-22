from milc import cli

from qmk.constants import QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.keyboard import keyboard_completer, keyboard_folder_or_all
from qmk.keymap import keymap_completer, is_keymap_target
from qmk.userspace import UserspaceDefs


@cli.argument('-kb', '--keyboard', type=keyboard_folder_or_all, completer=keyboard_completer, help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.subcommand('Adds a build target to userspace `qmk.json`.')
def userspace_add(cli):
    if not HAS_QMK_USERSPACE:
        cli.log.error('Could not determine QMK userspace location. Please run `qmk doctor` or `qmk userspace-doctor` to diagnose.')
        return False

    if not is_keymap_target(cli.args.keyboard, cli.args.keymap):
        cli.log.error('Invalid keymap argument.')
        return False

    userspace = UserspaceDefs(QMK_USERSPACE / 'qmk.json')
    userspace.add_target(cli.args.keyboard, cli.args.keymap)
    return userspace.save()
