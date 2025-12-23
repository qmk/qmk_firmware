"""Functions that help us work with keyboards.
"""
from array import array
from functools import lru_cache
from math import ceil
from pathlib import Path
import os
from glob import glob

import qmk.path
from qmk.c_parse import parse_config_h_file
from qmk.json_schema import json_load
from qmk.makefile import parse_rules_mk_file

from qmk.keycodes import load_spec

import math

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
ENC_DRAWING_CHARACTERS = {
    "unicode": {
        "tl": "╭",
        "tr": "╮",
        "bl": "╰",
        "br": "╯",
        "vl": "▲",
        "vr": "▼",
        "v": "│",
        "h": "─",
    },
    "ascii": {
        "tl": " ",
        "tr": " ",
        "bl": "\\",
        "br": "/",
        "v": "|",
        "vl": "/",
        "vr": "\\",
        "h": "_",
    },
}


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


@lru_cache(maxsize=1)
def keyboard_alias_definitions():
    return json_load(Path('data/mappings/keyboard_aliases.hjson'))


def is_all_keyboards(keyboard):
    """Returns True if the keyboard is an AllKeyboards object.
    """
    if isinstance(keyboard, str):
        return (keyboard == 'all')
    return isinstance(keyboard, AllKeyboards)


def find_keyboard_from_dir():
    """Returns a keyboard name based on the user's current directory.
    """
    relative_cwd = qmk.path.under_qmk_userspace()
    if not relative_cwd:
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

    This checks aliases to resolve the actual path for a keyboard.
    """
    aliases = keyboard_alias_definitions()

    while keyboard in aliases:
        last_keyboard = keyboard
        keyboard = aliases[keyboard].get('target', keyboard)
        if keyboard == last_keyboard:
            break

    if not qmk.path.is_keyboard(keyboard):
        raise ValueError(f'Invalid keyboard: {keyboard}')

    return keyboard


def keyboard_aliases(keyboard):
    """Returns the list of aliases for the supplied keyboard.

    Includes the keyboard itself.
    """
    aliases = json_load(Path('data/mappings/keyboard_aliases.hjson'))

    if keyboard in aliases:
        keyboard = aliases[keyboard].get('target', keyboard)

    keyboards = set(filter(lambda k: aliases[k].get('target', '') == keyboard, aliases.keys()))
    keyboards.add(keyboard)
    keyboards = list(sorted(keyboards))
    return keyboards


def keyboard_folder_or_all(keyboard):
    """Returns the actual keyboard folder.

    This checks aliases to resolve the actual path for a keyboard.
    If the supplied argument is "all", it returns an AllKeyboards object.
    """
    if keyboard == 'all':
        return AllKeyboards()

    return keyboard_folder(keyboard)


def _find_name(path):
    """Determine the keyboard name by stripping off the base_path and filename.
    """
    return path.replace(base_path, "").rsplit(os.path.sep, 1)[0]


def keyboard_completer(prefix, action, parser, parsed_args):
    """Returns a list of keyboards for tab completion.
    """
    return list_keyboards()


@lru_cache(maxsize=None)
def list_keyboards():
    """Returns a list of all keyboards.
    """
    # We avoid pathlib here because this is performance critical code.
    kb_wildcard = os.path.join(base_path, "**", 'keyboard.json')
    paths = [path for path in glob(kb_wildcard, recursive=True) if os.path.sep + 'keymaps' + os.path.sep not in path]

    found = map(_find_name, paths)

    # Convert to posix paths for consistency
    found = map(lambda x: str(Path(x).as_posix()), found)

    return sorted(set(found))


def config_h(keyboard):
    """Parses all the config.h files for a keyboard.

    Args:
        keyboard: name of the keyboard

    Returns:
        a dictionary representing the content of the entire config.h tree for a keyboard
    """
    config = {}
    cur_dir = Path('keyboards')
    keyboard = Path(keyboard)

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
    keyboard = Path(keyboard)
    rules = parse_rules_mk_file(cur_dir / keyboard / 'rules.mk')

    for i, dir in enumerate(keyboard.parts):
        cur_dir = cur_dir / dir
        rules = parse_rules_mk_file(cur_dir / 'rules.mk', rules)

    return rules

KEY_ICONS = {
    # "KC_NO": '☒',
    # "KC_TRANSPARENT": '▽',
    "KC_NO": ' ',
    "KC_TRANSPARENT": ' ',
    "KC_SPACE": '␣',
    "QK_GRAVE_ESCAPE": '⎋ `',
    "KC_ESC": '⎋',
    "KC_LEFT": '←',
    "KC_UP": '↑',
    "KC_RIGHT": '→',
    "KC_DOWN": '↓',

    "KC_TAB": '⭾',
    "KC_ENTER": '⮐',
    "KC_BACKSPACE": '⌫',
    "KC_INSERT": '⎀',
    "KC_DELETE": '⌦',

    "KC_HOME": '⤒',
    "KC_END": '⤓',
    "KC_PAGE_UP": '⇞',
    "KC_PAGE_DOWN": '⇟',

    "KC_LEFT_SHIFT": '⇧', "KC_RIGHT_SHIFT": '⇧',
    "KC_LEFT_CTRL": '∧',  "KC_RIGHT_CTRL": '∧',
    "KC_LEFT_GUI": '◊',   "KC_RIGHT_GUI": '◊',
    "KC_LEFT_ALT": '⌥',   "KC_RIGHT_ALT": '⌥',

    "KC_CAPS_LOCK": '⇩A',
    "KC_NUM_LOCK": '⇩#',

    "KC_APP": '☰',
}

@lru_cache(maxsize=2)
def get_kc_idx(render_ascii = False):
    kc_spec = load_spec('latest')
    kc_idx = {}
    for value in kc_spec['keycodes'].values():
        key = value['key']
        label = value.get('label')
        if render_ascii == False:
            label = KEY_ICONS.get(key,label)
        if label == None or len(label) == 0:
           label = key
           if 'aliases' in value:
                for alias in value['aliases']:
                    if len(alias) < len(label):
                        label = alias
        kc_idx[key] = label
        if 'aliases' in value:
            for alias in value['aliases']:
                kc_idx[alias] = label

    return kc_idx

def render_kle(layout_data, layers=None, decode_keys=True):
    """Renders all keymap layers into KLE-compatible format
    """

    kle_rows = []
    kle_row = []
    kle_x = 0
    kle_y = 0
    kle_w = 1
    kle_fa = None

    kc_idx = get_kc_idx()

    for ki, key in enumerate(layout_data):
        x = key.get('x', 0)
        y = key.get('y', 0)
        w = key.get('w', 1)
        h = key.get('h', 1)

        layer_labels = []
        layer_fa = []
        if layers != None:
            for li, layer in enumerate(layers):
                if layer == None:
                    break
                layer_label = layers[li][ki]
                layer_label = kc_idx.get(layer_label, layer_label);
                if layer_label.startswith('KC_') or layer_label.startswith('QK_'):
                    layer_label = layer_label[3:]
                layer_label = layer_label.strip()
                layer_labels.append(layer_label)
                lif = max(1, min(4,math.floor(w * 8 / len(layer_label)))) if layer_label != '' else 4
                layer_fa.append(lif)

        label = '\n'.join(layer_labels)

        kle_key_attributes = {}

        if layer_fa != kle_fa:
            kle_key_attributes['fa'] = layer_fa
            kle_fa = layer_fa

        if (y != kle_y) or (x < kle_x):
            if len(kle_row) > 0:
                kle_rows.append(kle_row)
                kle_x = 0
                kle_row = []
            y_incr = round(y - (kle_y + 1),4)
            kle_y = y
            if y_incr != 0:
                kle_key_attributes['y'] = y_incr

        x_incr = 0
        if x != kle_x:
            x_incr = round(x - kle_x,4)
            if x_incr != 0:
                kle_key_attributes['x'] = x_incr

        if w != kle_w:
            kle_key_attributes['w'] = w
        if h != 1:
            kle_key_attributes['h'] = h

        # ISO Enter
        if x >= 0.25 and w == 1.25 and h == 2:
            kle_key_attributes['w2'] = 1.5
            kle_key_attributes['h2'] = 1
            kle_key_attributes['x2'] = -0.25

        # BA Enter
        if w == 1.5 and h == 2:
            kle_key_attributes['w2'] = 2.25
            kle_key_attributes['h2'] = 1
            kle_key_attributes['x2'] = -0.75
            kle_key_attributes['y2'] = 1

        if len(kle_key_attributes) > 0:
            kle_row.append(kle_key_attributes)
        kle_row.append(label)
        kle_x += w + x_incr;

    # Don't forget to emit the last row
    if len(kle_row) > 0:
        kle_rows.append(kle_row)

    return kle_rows;

def render_layouts_kle(info_json, labels=None):
    """Renders all the layouts from an `info_json` structure in KLE format
    """

    layouts = []

    for layout in info_json['layouts']:
        layout_data = info_json['layouts'][layout]['layout']
        layouts += [[{"a":4,"w":10,"d":True},"\n" + layout]]
        layouts += render_kle(layout_data, labels, decode_keys=False)

    return layouts

def render_layout(layout_data, render_ascii, key_labels=None):
    """Renders a single layout.
    """
    textpad = [array('u', ' ' * 200) for x in range(100)]
    style = 'ascii' if render_ascii else 'unicode'

    kc_idx = get_kc_idx(render_ascii)

    for ki, key in enumerate(layout_data):
        x = key.get('x', 0)
        y = key.get('y', 0)
        w = key.get('w', 1)
        h = key.get('h', 1)

        if key_labels:
            label = key_labels[ki]
            label = kc_idx.get(label, label);
            if label.startswith('KC_') or label.startswith('QK_'):
                label = label[3:]
        else:
            label = key.get('label', '')

        if len(label) == 0:
            label = ' '

        if 'encoder' in key:
            render_encoder(textpad, x, y, w, h, label, style)
        elif x >= 0.25 and w == 1.25 and h == 2:
            render_key_isoenter(textpad, x, y, w, h, label, style)
        elif w == 1.5 and h == 2:
            render_key_baenter(textpad, x, y, w, h, label, style)
        else:
            render_key_rect(textpad, x, y, w, h, label, style)

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


def render_key_rect(textpad, x, y, w, h, label, style):
    box_chars = BOX_DRAWING_CHARACTERS[style]
    x = ceil(x * 4)
    y = ceil(y * 3)
    w = ceil(w * 4)
    h = ceil(h * 3)

    label_len = w - 2
    label_leftover = label_len - len(label)

    if len(label) > label_len:
        label = label[:label_len]

    label_blank = ' ' * label_len
    label_border = box_chars['h'] * label_len
    label_middle = label + ' ' * label_leftover

    top_line = array('u', box_chars['tl'] + label_border + box_chars['tr'])
    lab_line = array('u', box_chars['v'] + label_middle + box_chars['v'])
    mid_line = array('u', box_chars['v'] + label_blank + box_chars['v'])
    bot_line = array('u', box_chars['bl'] + label_border + box_chars['br'])

    textpad[y][x:x + w] = top_line
    textpad[y + 1][x:x + w] = lab_line
    for i in range(h - 3):
        textpad[y + i + 2][x:x + w] = mid_line
    textpad[y + h - 1][x:x + w] = bot_line


def render_key_isoenter(textpad, x, y, w, h, label, style):
    box_chars = BOX_DRAWING_CHARACTERS[style]
    x = ceil(x * 4)
    y = ceil(y * 3)
    w = ceil(w * 4)
    h = ceil(h * 3)

    label_len = w - 1
    label_leftover = label_len - len(label)

    if len(label) > label_len:
        label = label[:label_len]

    label_blank = ' ' * (label_len - 1)
    label_border_top = box_chars['h'] * label_len
    label_border_bottom = box_chars['h'] * (label_len - 1)
    label_middle = label + ' ' * label_leftover

    top_line = array('u', box_chars['tl'] + label_border_top + box_chars['tr'])
    lab_line = array('u', box_chars['v'] + label_middle + box_chars['v'])
    crn_line = array('u', box_chars['bl'] + box_chars['tr'] + label_blank + box_chars['v'])
    mid_line = array('u', box_chars['v'] + label_blank + box_chars['v'])
    bot_line = array('u', box_chars['bl'] + label_border_bottom + box_chars['br'])

    textpad[y][x - 1:x + w] = top_line
    textpad[y + 1][x - 1:x + w] = lab_line
    textpad[y + 2][x - 1:x + w] = crn_line
    textpad[y + 3][x:x + w] = mid_line
    textpad[y + 4][x:x + w] = mid_line
    textpad[y + 5][x:x + w] = bot_line


def render_key_baenter(textpad, x, y, w, h, label, style):
    box_chars = BOX_DRAWING_CHARACTERS[style]
    x = ceil(x * 4)
    y = ceil(y * 3)
    w = ceil(w * 4)
    h = ceil(h * 3)

    label_len = w + 1
    label_leftover = label_len - len(label)

    if len(label) > label_len:
        label = label[:label_len]

    label_blank = ' ' * (label_len - 3)
    label_border_top = box_chars['h'] * (label_len - 3)
    label_border_bottom = box_chars['h'] * label_len
    label_middle = label + ' ' * label_leftover

    top_line = array('u', box_chars['tl'] + label_border_top + box_chars['tr'])
    mid_line = array('u', box_chars['v'] + label_blank + box_chars['v'])
    crn_line = array('u', box_chars['tl'] + box_chars['h'] + box_chars['h'] + box_chars['br'] + label_blank + box_chars['v'])
    lab_line = array('u', box_chars['v'] + label_middle + box_chars['v'])
    bot_line = array('u', box_chars['bl'] + label_border_bottom + box_chars['br'])

    textpad[y][x:x + w] = top_line
    textpad[y + 1][x:x + w] = mid_line
    textpad[y + 2][x:x + w] = mid_line
    textpad[y + 3][x - 3:x + w] = crn_line
    textpad[y + 4][x - 3:x + w] = lab_line
    textpad[y + 5][x - 3:x + w] = bot_line


def render_encoder(textpad, x, y, w, h, label, style):
    box_chars = ENC_DRAWING_CHARACTERS[style]
    x = ceil(x * 4)
    y = ceil(y * 3)
    w = ceil(w * 4)
    h = ceil(h * 3)

    label_len = w - 2
    label_leftover = label_len - len(label)

    if len(label) > label_len:
        label = label[:label_len]

    label_blank = ' ' * label_len
    label_border = box_chars['h'] * label_len
    label_middle = label + ' ' * label_leftover

    top_line = array('u', box_chars['tl'] + label_border + box_chars['tr'])
    lab_line = array('u', box_chars['vl'] + label_middle + box_chars['vr'])
    mid_line = array('u', box_chars['v'] + label_blank + box_chars['v'])
    bot_line = array('u', box_chars['bl'] + label_border + box_chars['br'])

    textpad[y][x:x + w] = top_line
    textpad[y + 1][x:x + w] = lab_line
    for i in range(h - 3):
        textpad[y + i + 2][x:x + w] = mid_line
    textpad[y + h - 1][x:x + w] = bot_line
