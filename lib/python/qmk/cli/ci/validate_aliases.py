"""Validates the list of keyboard aliases.
"""
from pathlib import Path

from milc import cli

from qmk.json_schema import json_load
from qmk.keyboard import resolve_keyboard, keyboard_folder


def _safe_keyboard_folder(target):
    try:
        return keyboard_folder(target)  # throws ValueError if it's invalid
    except Exception:
        return None


def _target_keyboard_exists(target):
    # If there's no target, then we can't build it.
    if not target:
        return False

    # If the target directory existed but there was no rules.mk or rules.mk was incorrectly parsed, then we can't build it.
    if not resolve_keyboard(target):
        return False

    # If the target directory exists but it itself has an invalid alias or invalid rules.mk, then we can't build it either.
    if not _safe_keyboard_folder(target):
        return False

    # As far as we can tell, we can build it!
    return True


@cli.subcommand('Validates the list of keyboard aliases.', hidden=True)
def ci_validate_aliases(cli):
    aliases = json_load(Path('data/mappings/keyboard_aliases.hjson'))

    success = True
    for alias in aliases.keys():
        target = aliases[alias].get('target', None)
        if not _target_keyboard_exists(target):
            cli.log.error(f'Keyboard alias {alias} has a target that doesn\'t exist: {target}')
            success = False

    return success
