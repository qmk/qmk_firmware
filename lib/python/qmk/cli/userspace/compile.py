# Copyright 2023-2024 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later
from pathlib import Path
from milc import cli

from qmk.constants import QMK_USERSPACE, HAS_QMK_USERSPACE
from qmk.commands import build_environment
from qmk.userspace import UserspaceDefs
from qmk.build_targets import JsonKeymapBuildTarget
from qmk.search import search_keymap_targets
from qmk.cli.mass_compile import mass_compile_targets
from qmk.util import maybe_exit_config


def _extra_arg_setter(target, extra_args):
    target.extra_args = extra_args


@cli.argument('-t', '--no-temp', arg_only=True, action='store_true', help="Remove temporary files during build.")
@cli.argument('-j', '--parallel', type=int, default=1, help="Set the number of parallel make jobs; 0 means unlimited.")
@cli.argument('-c', '--clean', arg_only=True, action='store_true', help="Remove object files before compiling.")
@cli.argument('-n', '--dry-run', arg_only=True, action='store_true', help="Don't actually build, just show the commands to be run.")
@cli.argument('-e', '--env', arg_only=True, action='append', default=[], help="Set a variable to be passed to make. May be passed multiple times.")
@cli.subcommand('Compiles the build targets specified in userspace `qmk.json`.')
def userspace_compile(cli):
    if not HAS_QMK_USERSPACE:
        cli.log.error('Could not determine QMK userspace location. Please run `qmk doctor` or `qmk userspace-doctor` to diagnose.')
        return False

    maybe_exit_config(should_exit=False, should_reraise=True)

    userspace = UserspaceDefs(QMK_USERSPACE / 'qmk.json')

    build_targets = []
    keyboard_keymap_targets = []
    for e in userspace.build_targets:
        if isinstance(e, Path):
            build_targets.append(JsonKeymapBuildTarget(e))
        elif isinstance(e, dict):
            f = e['env'] if 'env' in e else None
            keyboard_keymap_targets.append((e['keyboard'], e['keymap'], f))
    if len(keyboard_keymap_targets) > 0:
        build_targets.extend(search_keymap_targets(keyboard_keymap_targets))

    return mass_compile_targets(list(set(build_targets)), cli.args.clean, cli.args.dry_run, cli.config.userspace_compile.no_temp, cli.config.userspace_compile.parallel, **build_environment(cli.args.env))
