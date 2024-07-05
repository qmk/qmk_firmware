"""Command to look over a keyboard/keymap and check for common mistakes.
"""
from pathlib import Path

from milc import cli

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.info import info_json
from qmk.keyboard import keyboard_completer, keyboard_folder_or_all, is_all_keyboards, list_keyboards
from qmk.keymap import locate_keymap, list_keymaps
from qmk.path import keyboard
from qmk.git import git_get_ignored_files
from qmk.c_parse import c_source_files

CHIBIOS_CONF_CHECKS = ['chconf.h', 'halconf.h', 'mcuconf.h', 'board.h']
INVALID_KB_FEATURES = set(['encoder_map', 'dip_switch_map', 'combo', 'tap_dance', 'via'])


def _list_defaultish_keymaps(kb):
    """Return default like keymaps for a given keyboard
    """
    defaultish = ['ansi', 'iso', 'via']

    # This is only here to flag it as "testable", so it doesn't fly under the radar during PR
    defaultish.append('vial')

    keymaps = set()
    for x in list_keymaps(kb):
        if x in defaultish or x.startswith('default'):
            keymaps.add(x)

    return keymaps


def _get_code_files(kb, km=None):
    """Return potential keyboard/keymap code files
    """
    search_path = locate_keymap(kb, km).parent if km else keyboard(kb)

    code_files = []
    for file in c_source_files([search_path]):
        # Ignore keymaps when only globing keyboard files
        if not km and 'keymaps' in file.parts:
            continue
        code_files.append(file)

    return code_files


def _has_license(file):
    """Check file has a license header
    """
    # Crude assumption that first line of license header is a comment
    fline = open(file).readline().rstrip()
    return fline.startswith(("/*", "//"))


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


def _handle_invalid_features(kb, info):
    """Check for features that should never be enabled at the keyboard level
    """
    ok = True
    features = set(info.get('features', []))
    for found in features & INVALID_KB_FEATURES:
        ok = False
        cli.log.error(f'{kb}: Invalid keyboard level feature detected - {found}')
    return ok


def _chibios_conf_includenext_check(target):
    """Check the ChibiOS conf.h for the correct inclusion of the next conf.h
    """
    for i, line in enumerate(target.open()):
        if f'#include_next "{target.name}"' in line:
            return f'Found `#include_next "{target.name}"` on line {i} of {target}, should be `#include_next <{target.name}>` (use angle brackets, not quotes)'
    return None


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

    for file in _get_code_files(kb, km):
        if not _has_license(file):
            cli.log.error(f'{kb}/{km}: The file "{file}" does not have a license header!')
            ok = False

        if file.name in CHIBIOS_CONF_CHECKS:
            check_error = _chibios_conf_includenext_check(file)
            if check_error is not None:
                cli.log.error(f'{kb}/{km}: {check_error}')
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
    if not _handle_invalid_features(kb, kb_info):
        ok = False

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

    for file in _get_code_files(kb):
        if not _has_license(file):
            cli.log.error(f'{kb}: The file "{file}" does not have a license header!')
            ok = False

        if file.name in CHIBIOS_CONF_CHECKS:
            check_error = _chibios_conf_includenext_check(file)
            if check_error is not None:
                cli.log.error(f'{kb}: {check_error}')
                ok = False

    return ok


@cli.argument('--strict', action='store_true', help='Treat warnings as errors')
@cli.argument('-kb', '--keyboard', action='append', type=keyboard_folder_or_all, completer=keyboard_completer, help='Keyboard to check. May be passed multiple times.')
@cli.argument('-km', '--keymap', help='The keymap to check')
@cli.subcommand('Check keyboard and keymap for common mistakes.')
@automagic_keyboard
@automagic_keymap
def lint(cli):
    """Check keyboard and keymap for common mistakes.
    """
    # Determine our keyboard list
    if not cli.config.lint.keyboard:
        cli.log.error('Missing required arguments: --keyboard')
        cli.print_help()
        return False

    if isinstance(cli.config.lint.keyboard, str):
        # if provided via config - string not array
        keyboard_list = [cli.config.lint.keyboard]
    elif is_all_keyboards(cli.args.keyboard[0]):
        keyboard_list = list_keyboards()
    else:
        keyboard_list = cli.config.lint.keyboard

    failed = []

    # Lint each keyboard
    for kb in keyboard_list:
        # Determine keymaps to also check
        if cli.args.keymap == 'all':
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
