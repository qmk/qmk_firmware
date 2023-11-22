"""Functions for searching through QMK keyboards and keymaps.
"""
import contextlib
import functools
import fnmatch
import logging
import re
from typing import List, Tuple
from dotty_dict import dotty, Dotty
from milc import cli

from qmk.util import parallel_map
from qmk.info import keymap_json
from qmk.keyboard import list_keyboards, keyboard_folder
from qmk.keymap import list_keymaps, locate_keymap
from qmk.build_targets import KeyboardKeymapBuildTarget, BuildTarget


def _set_log_level(level):
    cli.acquire_lock()
    old = cli.log_level
    cli.log_level = level
    cli.log.setLevel(level)
    logging.root.setLevel(level)
    cli.release_lock()
    return old


@contextlib.contextmanager
def ignore_logging():
    old = _set_log_level(logging.CRITICAL)
    yield
    _set_log_level(old)


def _all_keymaps(keyboard):
    """Returns a list of tuples of (keyboard, keymap) for all keymaps for the given keyboard.
    """
    with ignore_logging():
        keyboard = keyboard_folder(keyboard)
        return [(keyboard, keymap) for keymap in list_keymaps(keyboard)]


def _keymap_exists(keyboard, keymap):
    """Returns the keyboard name if the keyboard+keymap combination exists, otherwise None.
    """
    with ignore_logging():
        return keyboard if locate_keymap(keyboard, keymap) is not None else None


def _load_keymap_info(kb_km):
    """Returns a tuple of (keyboard, keymap, info.json) for the given keyboard/keymap combination.
    """
    with ignore_logging():
        return (kb_km[0], kb_km[1], keymap_json(kb_km[0], kb_km[1]))


def expand_make_targets(targets: List[str]) -> List[Tuple[str, str]]:
    """Expand a list of make targets into a list of (keyboard, keymap) tuples.

    Caters for 'all' in either keyboard or keymap, or both.
    """
    split_targets = []
    for target in targets:
        split_target = target.split(':')
        if len(split_target) != 2:
            cli.log.error(f"Invalid build target: {target}")
            return []
        split_targets.append((split_target[0], split_target[1]))
    return expand_keymap_targets(split_targets)


def _expand_keymap_target(keyboard: str, keymap: str, all_keyboards: List[str] = None) -> List[Tuple[str, str]]:
    """Expand a keyboard input and keymap input into a list of (keyboard, keymap) tuples.

    Caters for 'all' in either keyboard or keymap, or both.
    """
    if all_keyboards is None:
        all_keyboards = list_keyboards()

    if keyboard == 'all':
        if keymap == 'all':
            cli.log.info('Retrieving list of all keyboards and keymaps...')
            targets = []
            for kb in parallel_map(_all_keymaps, all_keyboards):
                targets.extend(kb)
            return targets
        else:
            cli.log.info(f'Retrieving list of keyboards with keymap "{keymap}"...')
            keyboard_filter = functools.partial(_keymap_exists, keymap=keymap)
            return [(kb, keymap) for kb in filter(lambda e: e is not None, parallel_map(keyboard_filter, all_keyboards))]
    else:
        if keymap == 'all':
            cli.log.info(f'Retrieving list of keymaps for keyboard "{keyboard}"...')
            return _all_keymaps(keyboard)
        else:
            return [(keyboard, keymap)]


def expand_keymap_targets(targets: List[Tuple[str, str]]) -> List[Tuple[str, str]]:
    """Expand a list of (keyboard, keymap) tuples inclusive of 'all', into a list of explicit (keyboard, keymap) tuples.
    """
    overall_targets = []
    all_keyboards = list_keyboards()
    for target in targets:
        overall_targets.extend(_expand_keymap_target(target[0], target[1], all_keyboards))
    return list(sorted(set(overall_targets)))


def _construct_build_target_kb_km(e):
    return KeyboardKeymapBuildTarget(keyboard=e[0], keymap=e[1])


def _construct_build_target_kb_km_json(e):
    return KeyboardKeymapBuildTarget(keyboard=e[0], keymap=e[1], json=e[2])


def _filter_keymap_targets(target_list: List[Tuple[str, str]], filters: List[str] = []) -> List[BuildTarget]:
    """Filter a list of (keyboard, keymap) tuples based on the supplied filters.

    Optionally includes the values of the queried info.json keys.
    """
    if len(filters) == 0:
        cli.log.info('Preparing target list...')
        targets = list(parallel_map(_construct_build_target_kb_km, target_list))
    else:
        cli.log.info('Parsing data for all matching keyboard/keymap combinations...')
        valid_keymaps = [(e[0], e[1], dotty(e[2])) for e in parallel_map(_load_keymap_info, target_list)]

        function_re = re.compile(r'^(?P<function>[a-zA-Z]+)\((?P<key>[a-zA-Z0-9_\.]+)(,\s*(?P<value>[^#]+))?\)$')
        equals_re = re.compile(r'^(?P<key>[a-zA-Z0-9_\.]+)\s*=\s*(?P<value>[^#]+)$')

        for filter_expr in filters:
            function_match = function_re.match(filter_expr)
            equals_match = equals_re.match(filter_expr)

            if function_match is not None:
                func_name = function_match.group('function').lower()
                key = function_match.group('key')
                value = function_match.group('value')

                if value is not None:
                    if func_name == 'length':
                        valid_keymaps = filter(lambda e, key=key, value=value: key in e[2] and len(e[2].get(key)) == int(value), valid_keymaps)
                    elif func_name == 'contains':
                        valid_keymaps = filter(lambda e, key=key, value=value: key in e[2] and value in e[2].get(key), valid_keymaps)
                    else:
                        cli.log.warning(f'Unrecognized filter expression: {function_match.group(0)}')
                        continue

                    cli.log.info(f'Filtering on condition: {{fg_green}}{func_name}{{fg_reset}}({{fg_cyan}}{key}{{fg_reset}}, {{fg_cyan}}{value}{{fg_reset}})...')
                else:
                    if func_name == 'exists':
                        valid_keymaps = filter(lambda e, key=key: key in e[2], valid_keymaps)
                    elif func_name == 'absent':
                        valid_keymaps = filter(lambda e, key=key: key not in e[2], valid_keymaps)
                    else:
                        cli.log.warning(f'Unrecognized filter expression: {function_match.group(0)}')
                        continue

                    cli.log.info(f'Filtering on condition: {{fg_green}}{func_name}{{fg_reset}}({{fg_cyan}}{key}{{fg_reset}})...')

            elif equals_match is not None:
                key = equals_match.group('key')
                value = equals_match.group('value')
                cli.log.info(f'Filtering on condition: {{fg_cyan}}{key}{{fg_reset}} == {{fg_cyan}}{value}{{fg_reset}}...')

                def _make_filter(k, v):
                    expr = fnmatch.translate(v)
                    rule = re.compile(f'^{expr}$', re.IGNORECASE)

                    def f(e):
                        lhs = e[2].get(k)
                        lhs = str(False if lhs is None else lhs)
                        return rule.search(lhs) is not None

                    return f

                valid_keymaps = filter(_make_filter(key, value), valid_keymaps)
            else:
                cli.log.warning(f'Unrecognized filter expression: {filter_expr}')
                continue

        cli.log.info('Preparing target list...')
        valid_keymaps = [(e[0], e[1], e[2].to_dict() if isinstance(e[2], Dotty) else e[2]) for e in valid_keymaps]  # need to convert dotty_dict back to dict because it doesn't survive parallelisation
        targets = list(parallel_map(_construct_build_target_kb_km_json, list(valid_keymaps)))

    return targets


def search_keymap_targets(targets: List[Tuple[str, str]] = [('all', 'default')], filters: List[str] = []) -> List[BuildTarget]:
    """Search for build targets matching the supplied criteria.
    """
    return _filter_keymap_targets(expand_keymap_targets(targets), filters)


def search_make_targets(targets: List[str], filters: List[str] = []) -> List[BuildTarget]:
    """Search for build targets matching the supplied criteria.
    """
    return _filter_keymap_targets(expand_make_targets(targets), filters)
