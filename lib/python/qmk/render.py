"""Functions that help us render keyboard data.
"""
from array import array
from math import ceil
import shutil
import os

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


def _clamp(minvalue, value, maxvalue):
    return max(minvalue, min(value, maxvalue))


def _key_type(key):
    x = key.get('x', 0)
    w = key.get('w', 1)
    h = key.get('h', 1)

    if x >= 0.25 and w == 1.25 and h == 2:
        return "isoenter"
    elif w == 2.25 and h == 2:
        return "baenter"
    else:
        return "rect"


def _render_key_rect(textpad, x, y, w, h, label, box_chars):
    label_len = w - 2

    label_blank = ' ' * label_len
    label_border = box_chars['h'] * label_len
    label_middle = label.center(label_len)[:label_len]

    top_line = array('u', box_chars['tl'] + label_border + box_chars['tr'])
    lab_line = array('u', box_chars['v'] + label_middle + box_chars['v'])
    mid_line = array('u', box_chars['v'] + label_blank + box_chars['v'])
    bot_line = array('u', box_chars['bl'] + label_border + box_chars['br'])

    textpad[y][x:x + w] = top_line
    textpad[y + 1][x:x + w] = lab_line
    for i in range(h - 3):
        textpad[y + i + 2][x:x + w] = mid_line
    textpad[y + h - 1][x:x + w] = bot_line


def _render_key_isoenter(textpad, x, y, w, h, label, box_chars):
    label_len = w - 1

    label_blank = ' ' * (label_len - 1)
    label_border_top = box_chars['h'] * label_len
    label_border_bottom = box_chars['h'] * (label_len - 1)
    label_middle = label.center(label_len)[:label_len]

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


def _render_key_baenter(textpad, x, y, w, h, label, box_chars):
    label_len = w - 2

    label_blank = ' ' * (label_len - 3)
    label_border_top = box_chars['h'] * (label_len - 3)
    label_border_bottom = box_chars['h'] * label_len
    label_middle = label.center(label_len)[:label_len]

    top_line = array('u', box_chars['tl'] + label_border_top + box_chars['tr'])
    mid_line = array('u', box_chars['v'] + label_blank + box_chars['v'])
    crn_line = array('u', box_chars['tl'] + box_chars['h'] + box_chars['h'] + box_chars['br'] + label_blank + box_chars['v'])
    lab_line = array('u', box_chars['v'] + label_middle + box_chars['v'])
    bot_line = array('u', box_chars['bl'] + label_border_bottom + box_chars['br'])

    textpad[y][x + 3:x + w] = top_line
    textpad[y + 1][x + 3:x + w] = mid_line
    textpad[y + 2][x + 3:x + w] = mid_line
    textpad[y + 3][x:x + w] = crn_line
    textpad[y + 4][x:x + w] = lab_line
    textpad[y + 5][x:x + w] = bot_line


def render_layout(layout_data, render_ascii, key_labels=None):
    """Renders a single layout.
    """
    # skim over the layout to work out the bounds
    size = 0
    for key in layout_data:
        size = max(size, key.get('x', 0) + key.get('w', 1))

    # scale keys to fit terminal size - pick nearest even?
    terminal_width = _clamp(80, shutil.get_terminal_size().columns, 200)
    key_width = _clamp(4, terminal_width // size, 8) & ~1

    # allow env to override
    key_width = int(os.environ.get('KEY_WIDTH', key_width))

    style = 'ascii' if render_ascii else 'unicode'
    box_chars = BOX_DRAWING_CHARACTERS[style]
    textpad = [array('u', ' ' * (key_width * size)) for x in range(100)]

    for key in layout_data:
        if key_labels:
            label = key_labels.pop(0)
            if label.startswith('KC_'):
                label = label[3:]
        else:
            label = key.get('label', '')

        # scale up info.json coordinates
        x = ceil(key.get('x', 0) * key_width)
        y = ceil(key.get('y', 0) * 3)
        w = ceil(key.get('w', 1) * key_width)
        h = ceil(key.get('h', 1) * 3)

        _render_func = globals()[f'_render_key_{_key_type(key)}']
        _render_func(textpad, x, y, w, h, label, box_chars)

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
