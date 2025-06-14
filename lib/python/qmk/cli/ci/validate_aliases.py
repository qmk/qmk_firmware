"""Validates the list of keyboard aliases.
"""
from typing import Optional
from milc import MILC, cli

from qmk.keyboard import keyboard_folder, keyboard_alias_definitions


def _safe_keyboard_folder(target: str) -> Optional[str]:
    try:
        return keyboard_folder(target)  # throws ValueError if it's invalid
    except Exception:
        return None


def _target_keyboard_exists(target: Optional[str]) -> bool:
    # If there's no target, then we can't build it.
    if not target:
        return False

    # If the target directory exists but it itself has an invalid alias or invalid rules.mk, then we can't build it either.
    if not _safe_keyboard_folder(target):
        return False

    # As far as we can tell, we can build it!
    return True


@cli.subcommand('Validates the list of keyboard aliases.', hidden=True)
def ci_validate_aliases(cli: MILC) -> bool:
    aliases = keyboard_alias_definitions()

    success = True
    for alias in aliases.keys():
        target: Optional[str] = aliases[alias].get('target', None)
        if not _target_keyboard_exists(target):
            cli.log.error(f'Keyboard alias {alias} has a target that doesn\'t exist: {target}')
            success = False

    return success
