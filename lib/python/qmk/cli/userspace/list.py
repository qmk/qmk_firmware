# Copyright 2023 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later
from pathlib import Path
from dotty_dict import Dotty
from milc import cli

from qmk.constants import QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.userspace import UserspaceDefs
from qmk.build_targets import BuildTarget
from qmk.keyboard import is_all_keyboards, keyboard_folder
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
            elif isinstance(e, dict) or isinstance(e, Dotty):
                this_build_targets = search_keymap_targets([(e['keyboard'], e['keymap'])])
                if len(this_build_targets) > 0:
                    if 'env' in e:
                        for t in this_build_targets:
                            t.extra_args = e.get('env')
                    build_targets.extend(this_build_targets)
    else:
        build_targets = userspace.build_targets

    for e in build_targets:
        if isinstance(e, Path):
            # JSON keymap from userspace
            cli.log.info(f'JSON keymap: {{fg_cyan}}{e}{{fg_reset}}')
            continue
        elif isinstance(e, dict) or isinstance(e, Dotty):
            # keyboard/keymap dict from userspace
            keyboard = e['keyboard']
            keymap = e['keymap']
            extra_args = e.get('env')
        elif isinstance(e, BuildTarget):
            # BuildTarget from search_keymap_targets()
            keyboard = e.keyboard
            keymap = e.keymap
            extra_args = e.extra_args

        extra_args_str = ''
        if len(extra_args) > 0:
            extra_args_str = ', '.join([f'{{fg_cyan}}{k}={v}{{fg_reset}}' for k, v in extra_args.items()])
            extra_args_str = f' ({{fg_cyan}}{extra_args_str}{{fg_reset}})'

        if is_all_keyboards(keyboard) or is_keymap_target(keyboard_folder(keyboard), keymap):
            cli.log.info(f'Keyboard: {{fg_cyan}}{keyboard}{{fg_reset}}, keymap: {{fg_cyan}}{keymap}{{fg_reset}}{extra_args_str}')
        else:
            cli.log.warn(f'Keyboard: {{fg_cyan}}{keyboard}{{fg_reset}}, keymap: {{fg_cyan}}{keymap}{{fg_reset}}{extra_args_str} -- not found!')
