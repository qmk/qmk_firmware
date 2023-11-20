"""Functions that help us work with keyboards.
"""
from functools import lru_cache
from pathlib import Path
import os
from glob import glob
from layout_renderer import LayoutRenderer

import qmk.path
from qmk.c_parse import parse_config_h_file
from qmk.json_schema import json_load
from qmk.makefile import parse_rules_mk_file


class AllKeyboards:
    """Represents all keyboards.
    """
    def __str__(self):
        return 'all'

    def __repr__(self):
        return 'all'

    def __eq__(self, other):
        return isinstance(other, AllKeyboards)


base_path = os.path.join(os.getcwd(), "keyboards") + os.path.sep


def is_all_keyboards(keyboard):
    """Returns True if the keyboard is an AllKeyboards object.
    """
    return isinstance(keyboard, AllKeyboards)


def find_keyboard_from_dir():
    """Returns a keyboard name based on the user's current directory.
    """
    relative_cwd = qmk.path.under_qmk_firmware()

    if relative_cwd and len(relative_cwd.parts) > 1 and relative_cwd.parts[0] == 'keyboards':
        # Attempt to extract the keyboard name from the current directory
        current_path = Path('/'.join(relative_cwd.parts[1:]))

        if 'keymaps' in current_path.parts:
            # Strip current_path of anything after `keymaps`
            keymap_index = len(current_path.parts) - current_path.parts.index('keymaps') - 1
            current_path = current_path.parents[keymap_index]

        if qmk.path.is_keyboard(current_path):
            return str(current_path)


def find_readme(keyboard):
    """Returns the readme for this keyboard.
    """
    cur_dir = qmk.path.keyboard(keyboard)
    keyboards_dir = Path('keyboards')
    while not (cur_dir / 'readme.md').exists():
        if cur_dir == keyboards_dir:
            return None
        cur_dir = cur_dir.parent

    return cur_dir / 'readme.md'


def keyboard_folder(keyboard):
    """Returns the actual keyboard folder.

    This checks aliases and DEFAULT_FOLDER to resolve the actual path for a keyboard.
    """
    aliases = json_load(Path('data/mappings/keyboard_aliases.hjson'))

    while keyboard in aliases:
        last_keyboard = keyboard
        keyboard = aliases[keyboard].get('target', keyboard)
        if keyboard == last_keyboard:
            break

    keyboard = resolve_keyboard(keyboard)

    if not qmk.path.is_keyboard(keyboard):
        raise ValueError(f'Invalid keyboard: {keyboard}')

    return keyboard


def keyboard_folder_or_all(keyboard):
    """Returns the actual keyboard folder.

    This checks aliases and DEFAULT_FOLDER to resolve the actual path for a keyboard.
    If the supplied argument is "all", it returns an AllKeyboards object.
    """
    if keyboard == 'all':
        return AllKeyboards()

    return keyboard_folder(keyboard)


def _find_name(path):
    """Determine the keyboard name by stripping off the base_path and rules.mk.
    """
    return path.replace(base_path, "").replace(os.path.sep + "rules.mk", "")


def keyboard_completer(prefix, action, parser, parsed_args):
    """Returns a list of keyboards for tab completion.
    """
    return list_keyboards()


def list_keyboards(resolve_defaults=True):
    """Returns a list of all keyboards - optionally processing any DEFAULT_FOLDER.
    """
    # We avoid pathlib here because this is performance critical code.
    kb_wildcard = os.path.join(base_path, "**", "rules.mk")
    paths = [path for path in glob(kb_wildcard, recursive=True) if os.path.sep + 'keymaps' + os.path.sep not in path]

    found = map(_find_name, paths)
    if resolve_defaults:
        found = map(resolve_keyboard, found)

    return sorted(set(found))


@lru_cache(maxsize=None)
def resolve_keyboard(keyboard):
    cur_dir = Path('keyboards')
    rules = parse_rules_mk_file(cur_dir / keyboard / 'rules.mk')
    while 'DEFAULT_FOLDER' in rules and keyboard != rules['DEFAULT_FOLDER']:
        keyboard = rules['DEFAULT_FOLDER']
        rules = parse_rules_mk_file(cur_dir / keyboard / 'rules.mk')
    return keyboard


def config_h(keyboard):
    """Parses all the config.h files for a keyboard.

    Args:
        keyboard: name of the keyboard

    Returns:
        a dictionary representing the content of the entire config.h tree for a keyboard
    """
    config = {}
    cur_dir = Path('keyboards')
    keyboard = Path(resolve_keyboard(keyboard))

    for dir in keyboard.parts:
        cur_dir = cur_dir / dir
        config = {**config, **parse_config_h_file(cur_dir / 'config.h')}

    return config


def rules_mk(keyboard):
    """Get a rules.mk for a keyboard

    Args:
        keyboard: name of the keyboard

    Returns:
        a dictionary representing the content of the entire rules.mk tree for a keyboard
    """
    cur_dir = Path('keyboards')
    keyboard = Path(resolve_keyboard(keyboard))
    rules = parse_rules_mk_file(cur_dir / keyboard / 'rules.mk')

    for i, dir in enumerate(keyboard.parts):
        cur_dir = cur_dir / dir
        rules = parse_rules_mk_file(cur_dir / 'rules.mk', rules)

    return rules


def render_layout(layout_data, render_ascii, legends='label', key_labels=None):
    if key_labels is not None:
        for index, key in enumerate(layout_data):
            key['label'] = key_labels[index]
            if key['label'][:3] in ('KC_', 'QK_'):
                key['label'] = key['label'][3:]

    return LayoutRenderer(layout_data, use_ascii=render_ascii, legends=legends)


def render_layouts(info_json, render_ascii, legends='label'):
    """Renders all the layouts from an `info_json` structure.
    """
    layouts = {}

    for layout in info_json['layouts']:
        layout_data = info_json['layouts'][layout]['layout']
        layouts[layout] = render_layout(layout_data, render_ascii, legends)

    return layouts
