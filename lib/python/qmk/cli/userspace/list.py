from pathlib import Path
from milc import cli

from qmk.constants import QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.userspace import UserspaceDefs
from qmk.keyboard import is_all_keyboards
from qmk.keymap import is_keymap_target
from qmk.search import search_keymap_targets


@cli.argument('-e', '--expand', arg_only=True, action='store_true', help="Expands any use of `all` for either keyboard or keymap.")
@cli.subcommand('Lists the build targets specified in userspace `qmk.json`.')
def userspace_list(cli):
    if not HAS_QMK_USERSPACE:
        cli.log.error('Could not determine QMK userspace location. Please run `qmk doctor` or `qmk userspace-doctor` to diagnose.')
        return False

    userspace = UserspaceDefs(QMK_USERSPACE / 'qmk.json')

    if cli.args.expand:
        build_targets = []
        for e in userspace.build_targets:
            if isinstance(e, Path):
                build_targets.append(e)
            elif isinstance(e, dict):
                build_targets.extend(search_keymap_targets([(e['keyboard'], e['keymap'])]))
    else:
        build_targets = userspace.build_targets

    for e in build_targets:
        if isinstance(e, Path):
            # JSON keymap from userspace
            cli.log.info(f'JSON keymap: {{fg_cyan}}{e}{{fg_reset}}')
            continue
        elif isinstance(e, dict):
            # keyboard/keymap dict from userspace
            keyboard = e['keyboard']
            keymap = e['keymap']
        elif isinstance(e, tuple):
            # BuildTarget from search_keymap_targets()
            keyboard = e[0].keyboard
            keymap = e[0].keymap

        if is_all_keyboards(keyboard) or is_keymap_target(keyboard, keymap):
            cli.log.info(f'Keyboard: {{fg_cyan}}{keyboard}{{fg_reset}}, keymap: {{fg_cyan}}{keymap}{{fg_reset}}')
        else:
            cli.log.warn(f'Keyboard: {{fg_cyan}}{keyboard}{{fg_reset}}, keymap: {{fg_cyan}}{keymap}{{fg_reset}} -- not found!')
