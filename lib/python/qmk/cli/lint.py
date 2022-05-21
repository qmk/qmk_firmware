"""Command to look over a keyboard/keymap and check for common mistakes.
"""
from pathlib import Path

from milc import cli

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.info import info_json
from qmk.keyboard import keyboard_completer, list_keyboards
from qmk.keymap import locate_keymap
from qmk.path import is_keyboard, keyboard


def keymap_check(kb, km):
    """Perform the keymap level checks.
    """
    ok = True
    keymap_path = locate_keymap(kb, km)

    if not keymap_path:
        ok = False
        cli.log.error("%s: Can't find %s keymap.", kb, km)

    return ok


def rules_mk_assignment_only(keyboard_path):
    """Check the keyboard-level rules.mk to ensure it only has assignments.
    """
    current_path = Path()
    errors = []

    for path_part in keyboard_path.parts:
        current_path = current_path / path_part
        rules_mk = current_path / 'rules.mk'

        if rules_mk.exists():
            continuation = None

            for i, line in enumerate(rules_mk.open()):
                line = line.strip()

                if '#' in line:
                    line = line[:line.index('#')]

                if continuation:
                    line = continuation + line
                    continuation = None

                if line:
                    if line[-1] == '\\':
                        continuation = line[:-1]
                        continue

                    if line and '=' not in line:
                        errors.append(f'Non-assignment code on line +{i} {rules_mk}: {line}')

    return errors


@cli.argument('--strict', action='store_true', help='Treat warnings as errors')
@cli.argument('-kb', '--keyboard', completer=keyboard_completer, help='Comma separated list of keyboards to check')
@cli.argument('-km', '--keymap', help='The keymap to check')
@cli.argument('--all-kb', action='store_true', arg_only=True, help='Check all keyboards')
@cli.subcommand('Check keyboard and keymap for common mistakes.')
@automagic_keyboard
@automagic_keymap
def lint(cli):
    """Check keyboard and keymap for common mistakes.
    """
    failed = []

    # Determine our keyboard list
    if cli.args.all_kb:
        if cli.args.keyboard:
            cli.log.warning('Both --all-kb and --keyboard passed, --all-kb takes presidence.')

        keyboard_list = list_keyboards()
    elif not cli.config.lint.keyboard:
        cli.log.error('Missing required arguments: --keyboard or --all-kb')
        cli.print_help()
        return False
    else:
        keyboard_list = cli.config.lint.keyboard.split(',')

    # Lint each keyboard
    for kb in keyboard_list:
        if not is_keyboard(kb):
            cli.log.error('No such keyboard: %s', kb)
            continue

        # Gather data about the keyboard.
        ok = True
        keyboard_path = keyboard(kb)
        keyboard_info = info_json(kb)

        # Check for errors in the info.json
        if keyboard_info['parse_errors']:
            ok = False
            cli.log.error('%s: Errors found when generating info.json.', kb)

        if cli.config.lint.strict and keyboard_info['parse_warnings']:
            ok = False
            cli.log.error('%s: Warnings found when generating info.json (Strict mode enabled.)', kb)

        # Check the rules.mk file(s)
        rules_mk_assignment_errors = rules_mk_assignment_only(keyboard_path)
        if rules_mk_assignment_errors:
            ok = False
            cli.log.error('%s: Non-assignment code found in rules.mk. Move it to post_rules.mk instead.', kb)
            for assignment_error in rules_mk_assignment_errors:
                cli.log.error(assignment_error)

        # Keymap specific checks
        if cli.config.lint.keymap:
            if not keymap_check(kb, cli.config.lint.keymap):
                ok = False

        # Check if all non-data driven macros exist in <keyboard.h>
        for layout, data in keyboard_info['layouts'].items():
            # Matrix data should be a list with exactly two integers: [0, 1]
            if not data['c_macro'] and not all('matrix' in key_data.keys() or len(key_data) == 2 or all(isinstance(n, int) for n in key_data) for key_data in data['layout']):
                cli.log.error(f'{kb}: "{layout}" has no "matrix" definition in either "info.json" or "<keyboard>.h"!')
                ok = False

        # Report status
        if not ok:
            failed.append(kb)

    # Check and report the overall status
    if failed:
        cli.log.error('Lint check failed for: %s', ', '.join(failed))
        return False

    cli.log.info('Lint check passed!')
    return True
