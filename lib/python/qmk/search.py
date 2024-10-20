"""Functions for searching through QMK keyboards and keymaps.
"""
from dataclasses import dataclass
import contextlib
import functools
import fnmatch
import json
import logging
import re
from typing import Callable, Dict, List, Optional, Tuple, Union
from dotty_dict import dotty, Dotty
from milc import cli

from qmk.util import parallel_map
from qmk.info import keymap_json
from qmk.keyboard import list_keyboards, keyboard_folder
from qmk.keymap import list_keymaps, locate_keymap
from qmk.build_targets import KeyboardKeymapBuildTarget, BuildTarget


@dataclass
class KeyboardKeymapDesc:
    keyboard: str
    keymap: str
    data: dict = None
    extra_args: dict = None

    def __hash__(self) -> int:
        return self.keyboard.__hash__() ^ self.keymap.__hash__() ^ json.dumps(self.extra_args, sort_keys=True).__hash__()

    def __lt__(self, other) -> bool:
        return (self.keyboard, self.keymap, json.dumps(self.extra_args, sort_keys=True)) < (other.keyboard, other.keymap, json.dumps(other.extra_args, sort_keys=True))

    def load_data(self):
        data = keymap_json(self.keyboard, self.keymap)
        self.data = data.to_dict() if isinstance(data, Dotty) else data

    @property
    def dotty(self) -> Dotty:
        return dotty(self.data) if self.data is not None else None

    def to_build_target(self) -> KeyboardKeymapBuildTarget:
        target = KeyboardKeymapBuildTarget(keyboard=self.keyboard, keymap=self.keymap, json=self.data)
        target.extra_args = self.extra_args
        return target


# by using a class for filters, we dont need to worry about capturing values
# see details <https://github.com/qmk/qmk_firmware/pull/21090>
class FilterFunction:
    """Base class for filters.
    It provides:
        - __init__: capture key and value

    Each subclass should provide:
        - func_name: how it will be specified on CLI
            >>> qmk find -f <func_name>...
        - apply: function that actually applies the filter
            ie: return whether the input kb/km satisfies the condition
    """

    key: str
    value: Optional[str]

    func_name: str
    apply: Callable[[KeyboardKeymapDesc], bool]

    def __init__(self, key, value):
        self.key = key
        self.value = value


class Exists(FilterFunction):
    func_name = "exists"

    def apply(self, target_info: KeyboardKeymapDesc) -> bool:
        return self.key in target_info.dotty


class Absent(FilterFunction):
    func_name = "absent"

    def apply(self, target_info: KeyboardKeymapDesc) -> bool:
        return self.key not in target_info.dotty


class Length(FilterFunction):
    func_name = "length"

    def apply(self, target_info: KeyboardKeymapDesc) -> bool:
        info_dotty = target_info.dotty
        return (self.key in info_dotty and len(info_dotty[self.key]) == int(self.value))


class Contains(FilterFunction):
    func_name = "contains"

    def apply(self, target_info: KeyboardKeymapDesc) -> bool:
        info_dotty = target_info.dotty
        return (self.key in info_dotty and self.value in info_dotty[self.key])


def _get_filter_class(func_name: str, key: str, value: str) -> Optional[FilterFunction]:
    """Initialize a filter subclass based on regex findings and return it.
    None if no there's no filter with the name queried.
    """

    for subclass in FilterFunction.__subclasses__():
        if func_name == subclass.func_name:
            return subclass(key, value)

    return None


def filter_help() -> str:
    names = [f"'{f.func_name}'" for f in FilterFunction.__subclasses__()]
    return ", ".join(names[:-1]) + f" and {names[-1]}"


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


def _all_keymaps(keyboard) -> List[KeyboardKeymapDesc]:
    """Returns a list of KeyboardKeymapDesc for all keymaps for the given keyboard.
    """
    with ignore_logging():
        keyboard = keyboard_folder(keyboard)
        return [KeyboardKeymapDesc(keyboard, keymap) for keymap in list_keymaps(keyboard)]


def _keymap_exists(keyboard, keymap):
    """Returns the keyboard name if the keyboard+keymap combination exists, otherwise None.
    """
    with ignore_logging():
        return keyboard if locate_keymap(keyboard, keymap) is not None else None


def _load_keymap_info(target: KeyboardKeymapDesc) -> KeyboardKeymapDesc:
    """Ensures a KeyboardKeymapDesc has its data loaded.
    """
    with ignore_logging():
        target.load_data()  # Ensure we load the data first
        return target


def expand_make_targets(targets: List[Union[str, Tuple[str, Dict[str, str]]]]) -> List[KeyboardKeymapDesc]:
    """Expand a list of make targets into a list of KeyboardKeymapDesc.

    Caters for 'all' in either keyboard or keymap, or both.
    """
    split_targets = []
    for target in targets:
        extra_args = None
        if isinstance(target, tuple):
            split_target = target[0].split(':')
            extra_args = target[1]
        else:
            split_target = target.split(':')
        if len(split_target) != 2:
            cli.log.error(f"Invalid build target: {target}")
            return []
        split_targets.append(KeyboardKeymapDesc(split_target[0], split_target[1], extra_args=extra_args))
    return expand_keymap_targets(split_targets)


def _expand_keymap_target(target: KeyboardKeymapDesc, all_keyboards: List[str] = None) -> List[KeyboardKeymapDesc]:
    """Expand a keyboard input and keymap input into a list of KeyboardKeymapDesc.

    Caters for 'all' in either keyboard or keymap, or both.
    """
    if all_keyboards is None:
        all_keyboards = list_keyboards()

    if target.keyboard == 'all':
        if target.keymap == 'all':
            cli.log.info('Retrieving list of all keyboards and keymaps...')
            targets = []
            for kb in parallel_map(_all_keymaps, all_keyboards):
                targets.extend(kb)
            for t in targets:
                t.extra_args = target.extra_args
            return targets
        else:
            cli.log.info(f'Retrieving list of keyboards with keymap "{target.keymap}"...')
            keyboard_filter = functools.partial(_keymap_exists, keymap=target.keymap)
            return [KeyboardKeymapDesc(kb, target.keymap, extra_args=target.extra_args) for kb in filter(lambda e: e is not None, parallel_map(keyboard_filter, all_keyboards))]
    else:
        if target.keymap == 'all':
            cli.log.info(f'Retrieving list of keymaps for keyboard "{target.keyboard}"...')
            targets = _all_keymaps(target.keyboard)
            for t in targets:
                t.extra_args = target.extra_args
            return targets
        else:
            return [target]


def expand_keymap_targets(targets: List[KeyboardKeymapDesc]) -> List[KeyboardKeymapDesc]:
    """Expand a list of KeyboardKeymapDesc inclusive of 'all', into a list of explicit KeyboardKeymapDesc.
    """
    overall_targets = []
    all_keyboards = list_keyboards()
    for target in targets:
        overall_targets.extend(_expand_keymap_target(target, all_keyboards))
    return list(sorted(set(overall_targets)))


def _construct_build_target(e: KeyboardKeymapDesc):
    return e.to_build_target()


def _filter_keymap_targets(target_list: List[KeyboardKeymapDesc], filters: List[str] = []) -> List[KeyboardKeymapDesc]:
    """Filter a list of KeyboardKeymapDesc based on the supplied filters.

    Optionally includes the values of the queried info.json keys.
    """
    if len(filters) == 0:
        cli.log.info('Preparing target list...')
        targets = target_list
    else:
        cli.log.info('Parsing data for all matching keyboard/keymap combinations...')
        valid_targets = parallel_map(_load_keymap_info, target_list)

        function_re = re.compile(r'^(?P<function>[a-zA-Z]+)\((?P<key>[a-zA-Z0-9_\.]+)(,\s*(?P<value>[^#]+))?\)$')
        equals_re = re.compile(r'^(?P<key>[a-zA-Z0-9_\.]+)\s*=\s*(?P<value>[^#]+)$')

        for filter_expr in filters:
            function_match = function_re.match(filter_expr)
            equals_match = equals_re.match(filter_expr)

            if function_match is not None:
                func_name = function_match.group('function').lower()
                key = function_match.group('key')
                value = function_match.group('value')

                filter_class = _get_filter_class(func_name, key, value)
                if filter_class is None:
                    cli.log.warning(f'Unrecognized filter expression: {function_match.group(0)}')
                    continue
                valid_targets = filter(filter_class.apply, valid_targets)

                value_str = f", {{fg_cyan}}{value}{{fg_reset}}" if value is not None else ""
                cli.log.info(f'Filtering on condition: {{fg_green}}{func_name}{{fg_reset}}({{fg_cyan}}{key}{{fg_reset}}{value_str})...')

            elif equals_match is not None:
                key = equals_match.group('key')
                value = equals_match.group('value')
                cli.log.info(f'Filtering on condition: {{fg_cyan}}{key}{{fg_reset}} == {{fg_cyan}}{value}{{fg_reset}}...')

                def _make_filter(k, v):
                    expr = fnmatch.translate(v)
                    rule = re.compile(f'^{expr}$', re.IGNORECASE)

                    def f(e: KeyboardKeymapDesc):
                        lhs = e.dotty.get(k)
                        lhs = str(False if lhs is None else lhs)
                        return rule.search(lhs) is not None

                    return f

                valid_targets = filter(_make_filter(key, value), valid_targets)
            else:
                cli.log.warning(f'Unrecognized filter expression: {filter_expr}')
                continue

        cli.log.info('Preparing target list...')
        targets = list(sorted(set(valid_targets)))

    return targets


def search_keymap_targets(targets: List[Union[Tuple[str, str], Tuple[str, str, Dict[str, str]]]] = [('all', 'default')], filters: List[str] = []) -> List[BuildTarget]:
    """Search for build targets matching the supplied criteria.
    """
    def _make_desc(e):
        if len(e) == 3:
            return KeyboardKeymapDesc(keyboard=e[0], keymap=e[1], extra_args=e[2])
        else:
            return KeyboardKeymapDesc(keyboard=e[0], keymap=e[1])

    targets = map(_make_desc, targets)
    targets = _filter_keymap_targets(expand_keymap_targets(targets), filters)
    targets = list(set(parallel_map(_construct_build_target, list(targets))))
    return sorted(targets)


def search_make_targets(targets: List[Union[str, Tuple[str, Dict[str, str]]]], filters: List[str] = []) -> List[BuildTarget]:
    """Search for build targets matching the supplied criteria.
    """
    targets = _filter_keymap_targets(expand_make_targets(targets), filters)
    targets = list(set(parallel_map(_construct_build_target, list(targets))))
    return sorted(targets)
