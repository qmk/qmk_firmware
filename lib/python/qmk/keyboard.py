"""Functions that help us work with keyboards.
"""
from array import array
from math import ceil
from pathlib import Path
import os
from glob import glob

from qmk.c_parse import parse_config_h_file
from qmk.json_schema import json_load
from qmk.makefile import parse_rules_mk_file
from qmk.path import is_keyboard, under_qmk_firmware

BOX_DRAWING_CHARACTERS = {
    "unicode": {
        "tl": "┌",
        "tr": "┐",
        "bl": "└",
        "br": "┘",
        "v": "│",
        "h": "─",
    },
    "ascii": {
        "tl": " ",
        "tr": " ",
        "bl": "|",
        "br": "|",
        "v": "|",
        "h": "_",
    },
}

base_path = os.path.join(os.getcwd(), "keyboards") + os.path.sep


def find_keyboard_from_dir():
    """Returns a keyboard name based on the user's current directory.
    """
    relative_cwd = under_qmk_firmware()

    if relative_cwd and len(relative_cwd.parts) > 1 and relative_cwd.parts[0] == 'keyboards':
        # Attempt to extract the keyboard name from the current directory
        current_path = Path('/'.join(relative_cwd.parts[1:]))

        if 'keymaps' in current_path.parts:
            # Strip current_path of anything after `keymaps`
            keymap_index = len(current_path.parts) - current_path.parts.index('keymaps') - 1
            current_path = current_path.parents[keymap_index]

        if is_keyboard(current_path):
            return str(current_path)


def keyboard_folder(keyboard):
    """Returns the actual keyboard folder.

    This checks aliases and DEFAULT_FOLDER to resolve the actual path for a keyboard.
    """
    aliases = json_load(Path('data/mappings/keyboard_aliases.json'))

    if keyboard in aliases:
        keyboard = aliases[keyboard].get('target', keyboard)

    rules_mk_file = Path(base_path, keyboard, 'rules.mk')

    if rules_mk_file.exists():
        rules_mk = parse_rules_mk_file(rules_mk_file)
        keyboard = rules_mk.get('DEFAULT_FOLDER', keyboard)

    if not is_keyboard(keyboard):
        raise ValueError(f'Invalid keyboard: {keyboard}')

    return keyboard


def _find_name(path):
    """Determine the keyboard name by stripping off the base_path and rules.mk.
    """
    return path.replace(base_path, "").replace(os.path.sep + "rules.mk", "")


def keyboard_completer(prefix, action, parser, parsed_args):
    """Returns a list of keyboards for tab completion.
    """
    return list_keyboards()


def list_keyboards():
    """Returns a list of all keyboards.
    """
    # We avoid pathlib here because this is performance critical code.
    kb_wildcard = os.path.join(base_path, "**", "rules.mk")
    paths = [path for path in glob(kb_wildcard, recursive=True) if 'keymaps' not in path]

    return sorted(map(_find_name, paths))


def config_h(keyboard):
    """Parses all the config.h files for a keyboard.

    Args:
        keyboard: name of the keyboard

    Returns:
        a dictionary representing the content of the entire config.h tree for a keyboard
    """
    config = {}
    cur_dir = Path('keyboards')
    rules = rules_mk(keyboard)
    keyboard = Path(rules['DEFAULT_FOLDER'] if 'DEFAULT_FOLDER' in rules else keyboard)

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
    keyboard = Path(keyboard)
    cur_dir = Path('keyboards')
    rules = parse_rules_mk_file(cur_dir / keyboard / 'rules.mk')

    if 'DEFAULT_FOLDER' in rules:
        keyboard = Path(rules['DEFAULT_FOLDER'])

    for i, dir in enumerate(keyboard.parts):
        cur_dir = cur_dir / dir
        rules = parse_rules_mk_file(cur_dir / 'rules.mk', rules)

    return rules


def render_layout(layout_data, render_ascii, key_labels=None):
    """Renders a single layout.
    """
    textpad = [array('u', ' ' * 200) for x in range(50)]
    style = 'ascii' if render_ascii else 'unicode'
    box_chars = BOX_DRAWING_CHARACTERS[style]

    for key in layout_data:
        x = ceil(key.get('x', 0) * 4)
        y = ceil(key.get('y', 0) * 3)
        w = ceil(key.get('w', 1) * 4)
        h = ceil(key.get('h', 1) * 3)

        if key_labels:
            label = key_labels.pop(0)
            if label.startswith('KC_'):
                label = label[3:]
        else:
            label = key.get('label', '')

        label_len = w - 2
        label_leftover = label_len - len(label)

        if len(label) > label_len:
            label = label[:label_len]

        label_blank = ' ' * label_len
        label_border = box_chars['h'] * label_len
        label_middle = label + ' '*label_leftover  # noqa: yapf insists there be no whitespace around *

        top_line = array('u', box_chars['tl'] + label_border + box_chars['tr'])
        lab_line = array('u', box_chars['v'] + label_middle + box_chars['v'])
        mid_line = array('u', box_chars['v'] + label_blank + box_chars['v'])
        bot_line = array('u', box_chars['bl'] + label_border + box_chars['br'])

        textpad[y][x:x + w] = top_line
        textpad[y + 1][x:x + w] = lab_line
        for i in range(h - 3):
            textpad[y + i + 2][x:x + w] = mid_line
        textpad[y + h - 1][x:x + w] = bot_line

    lines = []
    for line in textpad:
        if line.tounicode().strip():
            lines.append(line.tounicode().rstrip())

    return '\n'.join(lines)


def render_layouts(info_json, render_ascii):
    """Renders all the layouts from an `info_json` structure.
    """
    layouts = {}

    for layout in info_json['layouts']:
        layout_data = info_json['layouts'][layout]['layout']
        layouts[layout] = render_layout(layout_data, render_ascii)

    return layouts
