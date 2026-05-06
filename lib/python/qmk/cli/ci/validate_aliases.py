"""Validates the list of keyboard aliases.
"""
from milc import cli

from qmk.keyboard import keyboard_folder, keyboard_alias_definitions


def _safe_keyboard_folder(target):
    try:
        return keyboard_folder(target)  # throws ValueError if it's invalid
    except Exception:
        return None


def _target_keyboard_exists(target):
    # If there's no target, then we can't build it.
    if not target:
        return False

    # If the target directory exists but it itself has an invalid alias or invalid rules.mk, then we can't build it either.
    if not _safe_keyboard_folder(target):
        return False

    # As far as we can tell, we can build it!
    return True


def _alias_not_self(alias):
    """Check if alias points to itself, either directly or within a circular reference
    """
    aliases = keyboard_alias_definitions()

    found = set()
    while alias in aliases:
        found.add(alias)
        alias = aliases[alias].get('target', alias)
        if alias in found:
            return False

    return True


@cli.subcommand('Validates the list of keyboard aliases.', hidden=True)
def ci_validate_aliases(cli):
    aliases = keyboard_alias_definitions()

    success = True
    for alias in aliases.keys():
        target = aliases[alias].get('target', None)
        if not _alias_not_self(alias):
            cli.log.error(f'Keyboard alias {alias} should not point to itself')
            success = False

        elif not _target_keyboard_exists(target):
            cli.log.error(f'Keyboard alias {alias} has a target that doesn\'t exist: {target}')
            success = False

    return success
