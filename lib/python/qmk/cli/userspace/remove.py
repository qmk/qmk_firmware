# Copyright 2023-2024 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later
from pathlib import Path
from milc import cli

from qmk.commands import parse_env_vars
from qmk.constants import QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.keyboard import keyboard_completer, keyboard_folder_or_all
from qmk.keymap import keymap_completer
from qmk.userspace import UserspaceDefs


@cli.argument('builds', nargs='*', arg_only=True, help="List of builds in form <keyboard>:<keymap>, or path to a keymap JSON file.")
@cli.argument('-kb', '--keyboard', type=keyboard_folder_or_all, completer=keyboard_completer, help='The keyboard to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-km', '--keymap', completer=keymap_completer, help='The keymap to build a firmware for. Ignored when a configurator export is supplied.')
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Extra variables to set during build. May be passed multiple times.")
@cli.subcommand('Removes a build target from userspace `qmk.json`.')
def userspace_remove(cli):
    if not HAS_QMK_USERSPACE:
        cli.log.error('Could not determine QMK userspace location. Please run `qmk doctor` or `qmk userspace-doctor` to diagnose.')
        return False

    build_env = None if len(cli.args.env) == 0 else parse_env_vars(cli.args.env)

    userspace = UserspaceDefs(QMK_USERSPACE / 'qmk.json')

    if len(cli.args.builds) > 0:
        json_like_targets = list([Path(p) for p in filter(lambda e: Path(e).exists() and Path(e).suffix == '.json', cli.args.builds)])
        make_like_targets = list(filter(lambda e: Path(e) not in json_like_targets, cli.args.builds))

        for e in json_like_targets:
            userspace.remove_target(json_path=e)

        for e in make_like_targets:
            s = e.split(':')
            userspace.remove_target(keyboard=s[0], keymap=s[1], build_env=build_env)

    else:
        userspace.remove_target(keyboard=cli.args.keyboard, keymap=cli.args.keymap, build_env=build_env)

    return userspace.save()
