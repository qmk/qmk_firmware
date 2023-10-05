"""Validates the list of keyboard aliases.
"""
from pathlib import Path

from milc import cli

from qmk.constants import QMK_FIRMWARE
from qmk.json_schema import json_load
from qmk.keyboard import resolve_keyboard, keyboard_folder


def _safe_keyboard_folder(target):
    try:
        return keyboard_folder(target)
    except Exception:
        return None


@cli.subcommand('Validates the list of keyboard aliases.', hidden=True)
def ci_validate_aliases(cli):
    aliases = json_load(Path('data/mappings/keyboard_aliases.hjson'))

    success = True
    for alias in aliases.keys():
        if alias == 'bm16a':
            pass
        target = aliases[alias].get('target', None)
        if not target or not (QMK_FIRMWARE / 'keyboards' / target).exists() or not resolve_keyboard(target) or not _safe_keyboard_folder(target):
            cli.log.error(f'Keyboard alias {alias} has a target that doesn\'t exist: {target}')
            success = False

    return success
