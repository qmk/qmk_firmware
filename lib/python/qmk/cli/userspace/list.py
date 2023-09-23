from milc import cli

from qmk.constants import QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.userspace import UserspaceDefs
from qmk.keyboard import keyboard_folder_or_all, is_all_keyboards
from qmk.keymap import is_keymap_target


@cli.subcommand('Lists the build targets specified in userspace `qmk.json`.')
def userspace_list(cli):
    if not HAS_QMK_USERSPACE:
        cli.log.error('Could not determine QMK userspace location. Please run `qmk doctor` or `qmk userspace-doctor` to diagnose.')
        return False

    userspace = UserspaceDefs(QMK_USERSPACE / 'qmk.json')
    for target in userspace.build_targets:
        keyboard = keyboard_folder_or_all(target['keyboard'])
        keymap = target['keymap']
        if is_all_keyboards(keyboard) or is_keymap_target(keyboard, keymap):
            cli.log.info(f'Keyboard: {{fg_cyan}}{keyboard}{{fg_reset}}, keymap: {{fg_cyan}}{keymap}{{fg_reset}}')
        else:
            cli.log.warn(f'Keyboard: {{fg_cyan}}{keyboard}{{fg_reset}}, keymap: {{fg_cyan}}{keymap}{{fg_reset}} -- not found!')
