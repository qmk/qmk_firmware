"""Functions that help us work with keyboards.
"""
from array import array
from math import ceil
import shutil

KEY_WIDTH = 4 if shutil.get_terminal_size().columns < 160 else 6
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


def render_key_rect(textpad, x, y, w, h, label, style):
    box_chars = BOX_DRAWING_CHARACTERS[style]
    x = ceil(x * KEY_WIDTH)
    y = ceil(y * 3)
    w = ceil(w * KEY_WIDTH)
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
    x = ceil(x * KEY_WIDTH)
    y = ceil(y * 3)
    w = ceil(w * KEY_WIDTH)
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
    x = ceil(x * KEY_WIDTH)
    y = ceil(y * 3)
    w = ceil(w * KEY_WIDTH)
    h = ceil(h * 3)

    label_len = w - 2
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

    textpad[y][x + 3:x + w] = top_line
    textpad[y + 1][x + 3:x + w] = mid_line
    textpad[y + 2][x + 3:x + w] = mid_line
    textpad[y + 3][x:x + w] = crn_line
    textpad[y + 4][x:x + w] = lab_line
    textpad[y + 5][x:x + w] = bot_line


def render_layout(layout_data, render_ascii, key_labels=None):
    """Renders a single layout.
    """
    textpad = [array('u', ' ' * 200) for x in range(100)]
    style = 'ascii' if render_ascii else 'unicode'

    for key in layout_data:
        x = key.get('x', 0)
        y = key.get('y', 0)
        w = key.get('w', 1)
        h = key.get('h', 1)

        if key_labels:
            label = key_labels.pop(0)
            if label.startswith('KC_'):
                label = label[3:]
        else:
            label = key.get('label', '')

        if x >= 0.25 and w == 1.25 and h == 2:
            render_key_isoenter(textpad, x, y, w, h, label, style)
        elif w == 2.25 and h == 2:
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
