"""Command to look over a keyboard/keymap and check for common mistakes.
"""
from pathlib import Path

from milc import cli

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.info import info_json
from qmk.keyboard import keyboard_completer, list_keyboards
from qmk.keymap import locate_keymap, list_keymaps
from qmk.path import is_keyboard, keyboard
from qmk.git import git_get_ignored_files


def _list_defaultish_keymaps(kb):
    """Return default like keymaps for a given keyboard
    """
    defaultish = ['ansi', 'iso', 'via']

    keymaps = set()
    for x in list_keymaps(kb):
        if x in defaultish or x.startswith('default'):
            keymaps.add(x)

    return keymaps


def _handle_json_errors(kb, info):
    """Convert any json errors into lint errors
    """
    ok = True
    # Check for errors in the json
    if info['parse_errors']:
        ok = False
        cli.log.error(f'{kb}: Errors found when generating info.json.')

    if cli.config.lint.strict and info['parse_warnings']:
        ok = False
        cli.log.error(f'{kb}: Warnings found when generating info.json (Strict mode enabled.)')
    return ok


def _rules_mk_assignment_only(kb):
    """Check the keyboard-level rules.mk to ensure it only has assignments.
    """
    keyboard_path = keyboard(kb)
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


def keymap_check(kb, km):
    """Perform the keymap level checks.
    """
    ok = True
    keymap_path = locate_keymap(kb, km)

    if not keymap_path:
        ok = False
        cli.log.error("%s: Can't find %s keymap.", kb, km)
        return ok

    # Additional checks
    invalid_files = git_get_ignored_files(keymap_path.parent.as_posix())
    for file in invalid_files:
        cli.log.error(f'{kb}/{km}: The file "{file}" should not exist!')
        ok = False

    return ok


def keyboard_check(kb):
    """Perform the keyboard level checks.
    """
    ok = True
    kb_info = info_json(kb)

    if not _handle_json_errors(kb, kb_info):
        ok = False

    # Additional checks
    rules_mk_assignment_errors = _rules_mk_assignment_only(kb)
    if rules_mk_assignment_errors:
        ok = False
        cli.log.error('%s: Non-assignment code found in rules.mk. Move it to post_rules.mk instead.', kb)
        for assignment_error in rules_mk_assignment_errors:
            cli.log.error(assignment_error)

    invalid_files = git_get_ignored_files(f'keyboards/{kb}/')
    for file in invalid_files:
        if 'keymap' in file:
            continue
        cli.log.error(f'{kb}: The file "{file}" should not exist!')
        ok = False

    return ok


@cli.argument('--strict', action='store_true', help='Treat warnings as errors')
@cli.argument('-kb', '--keyboard', completer=keyboard_completer, help='Comma separated list of keyboards to check')
@cli.argument('-km', '--keymap', help='The keymap to check')
@cli.argument('--all-kb', action='store_true', arg_only=True, help='Check all keyboards')
@cli.argument('--all-km', action='store_true', arg_only=True, help='Check all keymaps')
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
            cli.log.warning('Both --all-kb and --keyboard passed, --all-kb takes precedence.')

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

        # Determine keymaps to also check
        if cli.args.all_km:
            keymaps = list_keymaps(kb)
        elif cli.config.lint.keymap:
            keymaps = {cli.config.lint.keymap}
        else:
            keymaps = _list_defaultish_keymaps(kb)
            # Ensure that at least a 'default' keymap always exists
            keymaps.add('default')

        ok = True

        # keyboard level checks
        if not keyboard_check(kb):
            ok = False

        # Keymap specific checks
        for keymap in keymaps:
            if not keymap_check(kb, keymap):
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
