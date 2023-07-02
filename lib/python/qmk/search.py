"""Functions for searching through QMK keyboards and keymaps.
"""
import contextlib
import fnmatch
import logging
import multiprocessing
import re
from dotty_dict import dotty
from milc import cli

from qmk.info import keymap_json
import qmk.keyboard
import qmk.keymap


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
    with ignore_logging():
        return (keyboard, qmk.keymap.list_keymaps(keyboard))


def _keymap_exists(keyboard, keymap):
    with ignore_logging():
        return keyboard if qmk.keymap.locate_keymap(keyboard, keymap) is not None else None


def _load_keymap_info(keyboard, keymap):
    with ignore_logging():
        return (keyboard, keymap, keymap_json(keyboard, keymap))


def search_keymap_targets(keymap='default', filters=[], print_vals=[]):
    targets = []

    with multiprocessing.Pool() as pool:
        cli.log.info(f'Retrieving list of keyboards with keymap "{keymap}"...')
        target_list = []
        if keymap == 'all':
            kb_to_kms = pool.map(_all_keymaps, qmk.keyboard.list_keyboards())
            for targets in kb_to_kms:
                keyboard = targets[0]
                keymaps = targets[1]
                target_list.extend([(keyboard, keymap) for keymap in keymaps])
        else:
            target_list = [(kb, keymap) for kb in filter(lambda kb: kb is not None, pool.starmap(_keymap_exists, [(kb, keymap) for kb in qmk.keyboard.list_keyboards()]))]

        if len(filters) == 0:
            targets = [(kb, km, {}) for kb, km in target_list]
        else:
            cli.log.info('Parsing data for all matching keyboard/keymap combinations...')
            valid_keymaps = [(e[0], e[1], dotty(e[2])) for e in pool.starmap(_load_keymap_info, target_list)]

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

            targets = [(e[0], e[1], [(p, e[2].get(p)) for p in print_vals]) for e in valid_keymaps]

    return targets
