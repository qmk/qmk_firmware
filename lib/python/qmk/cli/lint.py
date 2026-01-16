"""Command to look over a keyboard/keymap and check for common mistakes.
"""
from dotty_dict import dotty
from pathlib import Path

from milc import cli

from qmk.decorators import automagic_keyboard, automagic_keymap
from qmk.info import info_json
from qmk.keyboard import keyboard_completer, keyboard_folder_or_all, is_all_keyboards, list_keyboards
from qmk.keymap import locate_keymap, list_keymaps
from qmk.path import keyboard
from qmk.git import git_get_ignored_files
from qmk.c_parse import c_source_files, preprocess_c_file
from qmk.json_schema import json_load

CHIBIOS_CONF_CHECKS = ['chconf.h', 'halconf.h', 'mcuconf.h', 'board.h']
INVALID_KB_FEATURES = set(['encoder_map', 'dip_switch_map', 'combo', 'tap_dance', 'via'])
INVALID_KM_NAMES = ['via', 'vial']


def _list_defaultish_keymaps(kb):
    """Return default like keymaps for a given keyboard
    """
    defaultish = ['ansi', 'iso']

    # This is only here to flag it as "testable", so it doesn't fly under the radar during PR
    defaultish.extend(INVALID_KM_NAMES)

    keymaps = set()
    for x in list_keymaps(kb, include_userspace=False):
        if x in defaultish or x.startswith('default'):
            keymaps.add(x)

    return keymaps


def _get_readme_files(kb, km=None):
    """Return potential keyboard/keymap readme files
    """
    search_path = locate_keymap(kb, km).parent if km else keyboard(kb)

    readme_files = []

    if not km:
        current_path = Path(search_path.parts[0])
        for path_part in search_path.parts[1:]:
            current_path = current_path / path_part
            readme_files.extend(current_path.glob('*readme.md'))

    for file in search_path.glob("**/*readme.md"):
        # Ignore keymaps when only globing keyboard files
        if not km and 'keymaps' in file.parts:
            continue
        readme_files.append(file)

    return set(readme_files)


def _get_build_files(kb, km=None):
    """Return potential keyboard/keymap build files
    """
    search_path = locate_keymap(kb, km).parent if km else keyboard(kb)

    build_files = []

    if not km:
        current_path = Path()
        for path_part in search_path.parts:
            current_path = current_path / path_part
            build_files.extend(current_path.glob('*rules.mk'))

    for file in search_path.glob("**/*rules.mk"):
        # Ignore keymaps when only globing keyboard files
        if not km and 'keymaps' in file.parts:
            continue
        build_files.append(file)

    return set(build_files)


def _get_code_files(kb, km=None):
    """Return potential keyboard/keymap code files
    """
    search_path = locate_keymap(kb, km).parent if km else keyboard(kb)

    code_files = []

    if not km:
        current_path = Path()
        for path_part in search_path.parts:
            current_path = current_path / path_part
            code_files.extend(current_path.glob('*.h'))
            code_files.extend(current_path.glob('*.c'))

    for file in c_source_files([search_path]):
        # Ignore keymaps when only globing keyboard files
        if not km and 'keymaps' in file.parts:
            continue
        code_files.append(file)

    return code_files


def _is_invalid_readme(file):
    """Check if file contains any unfilled content
    """
    tokens = [
        '%KEYBOARD%',
        '%REAL_NAME%',
        '%USER_NAME%',
        'image replace me!',
        'A short description of the keyboard/project',
        'The PCBs, controllers supported',
        'Links to where you can find this hardware',
    ]

    for line in file.read_text(encoding='utf-8').split("\n"):
        if any(token in line for token in tokens):
            return True
    return False


def _is_empty_rules(file):
    """Check if file contains any useful content
    """
    for line in file.read_text(encoding='utf-8').split("\n"):
        if len(line) > 0 and not line.isspace() and not line.startswith('#'):
            return False
    return True


def _is_empty_include(file):
    """Check if file contains any useful content
    """
    for line in preprocess_c_file(file).split("\n"):
        if len(line) > 0 and not line.isspace() and not line.startswith('#pragma once'):
            return False
    return True


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


def _handle_invalid_config(kb, info):
    """Check for invalid keyboard level config
    """
    if info.get('url') == "":
        cli.log.warning(f'{kb}: Invalid keyboard level config detected - Optional field "url" should not be empty.')
    return True


def _chibios_conf_includenext_check(target):
    """Check the ChibiOS conf.h for the correct inclusion of the next conf.h
    """
    for i, line in enumerate(target.open()):
        if f'#include_next "{target.name}"' in line:
            return f'Found `#include_next "{target.name}"` on line {i} of {target}, should be `#include_next <{target.name}>` (use angle brackets, not quotes)'
    return None


def _rules_mk_assignment_only(rules_mk):
    """Check the keyboard-level rules.mk to ensure it only has assignments.
    """
    errors = []
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


def _handle_duplicating_code_defaults(kb, info):
    def _collect_dotted_output(kb_info_json, prefix=''):
        """Print the info.json in a plain text format with dot-joined keys.
        """
        for key in sorted(kb_info_json):
            new_prefix = f'{prefix}.{key}' if prefix else key

            if isinstance(kb_info_json[key], dict):
                yield from _collect_dotted_output(kb_info_json[key], new_prefix)
            elif isinstance(kb_info_json[key], list):
                # TODO: handle non primitives?
                yield (new_prefix, kb_info_json[key])
            else:
                yield (new_prefix, kb_info_json[key])

    defaults_map = json_load(Path('data/mappings/info_defaults.hjson'))
    dotty_info = dotty(info)

    for key, v_default in _collect_dotted_output(defaults_map):
        v_info = dotty_info.get(key)
        if v_default == v_info:
            cli.log.warning(f'{kb}: Option "{key}" duplicates default value of "{v_default}"')

    return True


def keymap_check(kb, km):
    """Perform the keymap level checks.
    """
    ok = True
    keymap_path = locate_keymap(kb, km)

    if not keymap_path:
        ok = False
        cli.log.error("%s: Can't find %s keymap.", kb, km)
        return ok

    if km in INVALID_KM_NAMES:
        ok = False
        cli.log.error("%s: The keymap %s should not exist!", kb, km)
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


def keyboard_check(kb):  # noqa C901
    """Perform the keyboard level checks.
    """
    ok = True
    kb_info = info_json(kb)

    if not _handle_json_errors(kb, kb_info):
        ok = False

    # Additional checks
    if not _handle_invalid_features(kb, kb_info):
        ok = False

    if not _handle_invalid_config(kb, kb_info):
        ok = False

    if not _handle_duplicating_code_defaults(kb, kb_info):
        ok = False

    invalid_files = git_get_ignored_files(f'keyboards/{kb}/')
    for file in invalid_files:
        if 'keymap' in file:
            continue
        cli.log.error(f'{kb}: The file "{file}" should not exist!')
        ok = False

    if not _get_readme_files(kb):
        cli.log.error(f'{kb}: Is missing a readme.md file!')
        ok = False

    for file in _get_readme_files(kb):
        if _is_invalid_readme(file):
            cli.log.error(f'{kb}: The file "{file}" still contains template tokens!')
            ok = False

    for file in _get_build_files(kb):
        if _is_empty_rules(file):
            cli.log.error(f'{kb}: The file "{file}" is effectively empty and should be removed!')
            ok = False

        if file.suffix in ['rules.mk']:
            rules_mk_assignment_errors = _rules_mk_assignment_only(file)
            if rules_mk_assignment_errors:
                ok = False
                cli.log.error('%s: Non-assignment code found in rules.mk. Move it to post_rules.mk instead.', kb)
                for assignment_error in rules_mk_assignment_errors:
                    cli.log.error(assignment_error)

    for file in _get_code_files(kb):
        if not _has_license(file):
            cli.log.error(f'{kb}: The file "{file}" does not have a license header!')
            ok = False

        if file.name in ['config.h']:
            if _is_empty_include(file):
                cli.log.error(f'{kb}: The file "{file}" is effectively empty and should be removed!')
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
    elif any(is_all_keyboards(kb) for kb in cli.args.keyboard):
        keyboard_list = list_keyboards()
    else:
        keyboard_list = list(set(cli.config.lint.keyboard))

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
