"""Validates the list of keyboard targets.
"""
from milc import cli

from pathlib import Path


@cli.subcommand('Validates the list of keyboard targets.', hidden=True)
def ci_validate_keyboard_targets(cli):
    errors = set()

    for rules_mk in Path('keyboards').glob('**/rules.mk'):
        if any({'keymaps', 'common', 'lib'} & set(rules_mk.parts)):
            continue

        folder = rules_mk.parent
        if not any(folder.glob('**/keyboard.json')):
            errors.add(folder)

    for keymap in Path('keyboards').glob('**/keymaps/'):
        folder = keymap.parent
        if not any(folder.glob('**/keyboard.json')):
            errors.add(folder)

    for error in errors:
        print(f"{error}::Legacy target detected")

    exit(min(len(errors), 255))
