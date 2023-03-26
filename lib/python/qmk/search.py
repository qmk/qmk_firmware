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


def search_keymap_targets(keymap='default', filters=[]):
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
            targets = target_list
        else:
            cli.log.info('Parsing data for all matching keyboard/keymap combinations...')
            valid_keymaps = [(e[0], e[1], dotty(e[2])) for e in pool.starmap(_load_keymap_info, target_list)]

            equals_re = re.compile(r'^(?P<key>[a-zA-Z0-9_\.]+)\s*=\s*(?P<value>[^#]+)$')
            exists_re = re.compile(r'^exists\((?P<key>[a-zA-Z0-9_\.]+)\)$')
            for filter_txt in filters:
                f = equals_re.match(filter_txt)
                if f is not None:
                    key = f.group('key')
                    value = f.group('value')
                    cli.log.info(f'Filtering on condition ("{key}" == "{value}")...')

                    def _make_filter(k, v):
                        expr = fnmatch.translate(v)
                        rule = re.compile(f'^{expr}$', re.IGNORECASE)

                        def f(e):
                            lhs = e[2].get(k)
                            lhs = str(False if lhs is None else lhs)
                            return rule.search(lhs) is not None

                        return f

                    valid_keymaps = filter(_make_filter(key, value), valid_keymaps)

                f = exists_re.match(filter_txt)
                if f is not None:
                    key = f.group('key')
                    cli.log.info(f'Filtering on condition (exists: "{key}")...')
                    valid_keymaps = filter(lambda e: e[2].get(key) is not None, valid_keymaps)

            targets = [(e[0], e[1]) for e in valid_keymaps]

    return targets
