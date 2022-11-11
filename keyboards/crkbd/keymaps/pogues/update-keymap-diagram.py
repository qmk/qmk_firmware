#!/usr/bin/python

# ============================================
#   Creates an SVG keymap diagram by parsing
#   my qmk keymap.c file, including RGB LED
#   colours.
#
#   Based heavily off the file by Matt Gemmell
#   Web:        https://mattgemmell.com/
#   Twitter:    https://twitter.com/mattgemmell
#   GitHub:     https://github.com/mattgemmell
#
# ============================================

# TODO
#  1.   need to add the combos to the keymap
#  2.   add non adjacent combos to a different section
#  3.   look at tidying up the templates so you dont need to pass the constants - what about f strings
#  4.   svg_for_compose could be broken up
#  5.   look at the text anchors for the combo comments... left align?
#  5.   general code tidy up??
#  6.   fancy combo mappings for non adjacent keys

import argparse
from collections import OrderedDict
from string import Template
import re


class SVG:
    diagram_inset = 10 # horizontal and vertical, around entire diagram
    layer_spacing = 30 # vertical spacing between each layer
    key_width = 65
    key_height = 55
    key_radius = 6 # corner radius
    key_spacing = 4 # horizontal and vertical, both between keys and around entire layer
    last_row_pad = 20 # additional vertical spacing (added to key_spacing) for final row

    split_spacing = 40 # if using split keyboard this is the gap between the sides

    layer_title_height = 20
    layer_title_spacing = 15

    held_css_class = 'held'
    mods_css_class = 'mods'
    blank_css_class = 'blank'
    transparent_css_class = 'transparent'

keycode_blank = 'NO'
transparent_keycodes = ('_______', 'KC_TRNS')

_LAYERS = ('LSYM', 'LNUM')
_LAYER_KEYS = (('TD', 'TD_'), ('TT', ''), ('OSL', ''), ('MO', ''))
def _layer_keys(l):
    return [f'{m}({p}{l})' for (m, p) in _LAYER_KEYS]

annotation_keycodes = {
    'layer': [f'{m}({p}{l})' for (m, p) in _LAYER_KEYS for l in _LAYERS],
    'one-shot': ['OSM_ALT', 'OSM_GUI', 'OSM_CTL', 'OSM_SFT'],
    'held': []
}

# SVG template segments
svg_header_template = Template('''<svg width="${svg_width}" height="${svg_height}" viewBox="0 0 ${svg_width} ${svg_height}" xmlns="http://www.w3.org/2000/svg" class="">
<style>
    svg {
        font-family: -apple-system, "Helvetica Neue", sans-serif;
        font-size: 14px;
        text-rendering: optimizeLegibility;
        background-color: white;
    }
    text {
        text-anchor: middle;
        dominant-baseline: middle;
    }
    .text-container > div {
        cursor: default;
        box-sizing: border-box;
        background-color: #f0f0f0;
        text-align: center;
        width: ${key_width}px;
        height: ${key_height}px;
        border-radius: ${key_radius}px;
        display: flex;
        flex-direction: column;
        overflow: hidden;
    }
    .combo-font {
        font-family: -apple-system, "Helvetica Neue", sans-serif;
        font-size: 12px;
        text-rendering: optimizeLegibility;
    }
    .glyph {
        padding: 1px 2px;
        display: flex;
        justify-content: center;
        align-items: center;
        hyphens: auto;
        -webkit-hyphens: auto;
        -moz-hyphens: auto;
        -ms-hyphens: auto;
        flex: 1 0 auto;
    }
    .text-container > div:after {
        box-sizing: border-box;
        font-size: 11px;
        font-weight: bold;
        font-variant: small-caps;
        position: fixed;
        bottom: 0;
        padding-bottom: 1px;
        width: 100%;
        display: none;
    }
    .text-container > div.${held_css_class} > .glyph { background-color: #bbf; }
    .text-container > div.${mods_css_class} > .glyph { background-color: #afa; }
    .rgb .text-container > div.${held_css_class} > .glyph {
        background-color: initial;
        border: 3px solid #00e;
        border-bottom-width: 0;
        border-radius: ${key_radius}px ${key_radius}px 0 0;
    }
    .text-container > div.${blank_css_class} { }
    .text-container > div.${transparent_css_class} { }
    .layer_title {
        font-size: 17px;
        font-weight: bold;
        fill: #777;
    }
    .layer_bg {
        fill: #c0c0c0;
        width: ${layer_bg_width}px;
        height: ${layer_bg_height}px;
    }
    .kc_up, .kc_down, .kc_left, .kc_right,
    .kc_ent, .kc_bspc, .os_caps, .kc_esc,
    .kc_lsft, .nav_spc,
    .kc_exlm, .kc_at, .kc_hash, .kc_dlr, .kc_perc,
    .kc_ampr, .kc_astr, .kc_unds, .kc_mins,
    .kc_pipe, .kc_scln, .kc_eql, .kc_coln, .kc_tild,
    .kc_lt, .kc_gt, .kc_grv, .kc_circ, .kc_plus, .kc_bsls,
    .kc_quot, .kc_dot, .kc_comm, .kc_slsh,
    .os_shft, .os_ctrl, .os_alt, .os_cmd,
    .kc_mac_spotlight, .kc_pgup, .kc_pgdn,
    .kc_mac_undo, .kc_mac_redo, .kc_tab,
    .kc_mac_cut, .kc_spc, .kc_mac_lock_scrn,
    .kc_brightness_up, .kc_brightness_down,
    .kc_volu, .kc_vold, .kc_mute,
    .kc_mply, .kc_mprv, .kc_mnxt {
        font-size: 18px;
    }
    .kc_bspc { font-size: 22px; }
    .os_caps { font-size: 19px; padding-top: 4px !important; }
    .kc_mac_spotlight { font-size: 40px; }
    .kc_mac_undo { font-size: 34px; }
    .kc_mac_redo { font-size: 34px; }
    .kc_mac_cut { font-size: 20px; }
    .kc_spc { font-size: 24px; }
    .kc_mac_lock_scrn { font-size: 22px; }
    .kc_brightness_up { font-size: 28px; }
    .kc_brightness_down { font-size: 32px; }
    .kc_audio_vol_down { font-size: 22px; }
    .kc_audio_vol_up { font-size: 22px; }
    .kc_audio_mute { font-size: 22px; }
    .kc_media_play_pause { font-size: 26px; }
    .kc_media_prev_track { font-size: 26px; }
    .kc_media_next_track { font-size: 26px; }
    .annotation {
        box-sizing: border-box;
        font-size: 11px;
        font-weight: bold;
        font-variant: small-caps;
        padding-bottom: 2px;
        width: 100%;
        color: #f6f6f6;
        background-color: #666;
    }
    .${held_css_class} .annotation.layer { background-color: #00e; }
    .${mods_css_class} .annotation.layer { background-color: #0c0; color: #222; }
</style>
''')

svg_footer = '''
</svg>
'''

svg_layer_title_template = Template('''
<text x="${layer_title_x}" y="${layer_title_y}" class="layer_title">${layer_title}</text>
''')

svg_layer_bg_template = Template('''
<rect rx="${key_radius}" x="${layer_bg_x}" y="${layer_bg_y}" class="layer_bg" />
''')

svg_key_template = Template('''
<foreignObject x="${key_x}" y="${key_y}" width="${key_width}" height="${key_height}" class="text-container">
    <div xmlns="http://www.w3.org/1999/xhtml" lang="en" class="${key_classes}"><div class="glyph">${key_label}</div>${annotation}</div>
</foreignObject>
''')

LAYER_DISPLAY_NAMES = {
    'LCMK': 'Colemak - DH',
    'LSYM': 'Symbols',
    'LNUM': 'Numbers',
    'LFUN': 'Function Keys',
    'LMOV': 'Movement Keys',
    'LMSE': 'Mouse Keys',
    'LQWE': 'QWERTY',


    # for wayne
    '_DEF': 'QWERTY',
    '_NUM': 'Numbers',
    '_SYM': 'Symbols',
    '_NAV': 'Navigation',
    '_FUN': 'Function',
    '_WNAV': 'Win Nav',
}

LAYER_HELD_KEYCODES = {  # indicate which keys are held to get to a layer
    'LSYM': [f'{m}({p}LSYM)' for (m, p) in _LAYER_KEYS],
    'LNUM': [f'{m}({p}LNUM)' for (m, p) in _LAYER_KEYS],
    'LMOV': [f'{m}({p}LMOV)' for (m, p) in _LAYER_KEYS],
    'LFUN': [f'{m}({p}{l})' for (m, p) in _LAYER_KEYS for l in _LAYERS],
    'LMOV': ['MOV_SPC'],
}

MODS_HELD_KEYCODES = {
    # indicate which keys are dual role tap/mods
    # here we list the mods key, the tap is defined in key_names
    'CTL_BSP': 'Ctrl',
    'CTL_SPC': 'Ctrl',
    'CTL_Z': 'Ctrl',
    'CTL_SLS': 'Ctrl',
    'CTL_W': 'Ctrl',
    'CTL_Y': 'Ctrl',
    'SFT_SPC': 'Shift',
    'SFT_BSP': 'Shift',
    'SFT_Z': 'Shift',
    'SFT_SLS': 'Shift',
    'SFT_QUO': 'Shift',
    'MOV_SPC': 'Mov',
}

keycode_prefix = 'KC_'
key_names = {
    "KC_NO": "",
    "M_UNDO": "Undo",
    "C(KC_Z)": "Undo",
    "M_CUT": "Cut",
    "C(KC_X)": "Cut",
    "M_COPY": "Copy",
    "C(KC_C)": "Copy",
    "M_PSTE": "Paste",
    "C(KC_V)": "Paste",
    "M_SAVE": "Save",
    "W1": "W1",
    "W2": "W2",
    "W3": "W3",
    "W4": "W4",
    "W5": "W5",
    "W6": "W6",
    "TG_QWTY": "To QWERTY",
    "KC_HOME": "Home",
    "KC_END": "End",
    "KC_DEL": "Del",
    "TAB_L": "Prev Tab",
    "TAB_R": "Next Tab",
    "ALF": "Alfred",
    "HOOK": "Hook",
    "LHLF": "Resize left",
    "RHLF": "Resize right",
    "FULL": "Resize full",
    "OS_SHFT": "&#8679;",
    "OS_CTRL": "&#94;",
    "OS_ALT": "&#8997;",
    "OS_CMD": "&#8984;",
    "SW_APP": "Switch App",
    "KC_LSFT": "&#8679;",
    "NAV_SPC": "&#9251;",
    "NUM": "Num",
    "SYM": "Sym",
    "WNAV": "Work space",
    "FUN": "Fun",
    "KC_VOLD": "&#128265;",
    "KC_MUTE": "&#128263;",
    "KC_VOLU": "&#128266;",
    "KC_MPRV": "&#9198;",
    "KC_MPLY": "&#9199;",
    "KC_MNXT": "&#9197;",
    "KC_QUOT": "'",
    "MY_DQUO": '"',
    "KC_COMM": ",",
    "KC_DOT": ".",
    "KC_SLSH": "/",
    "KC_SPC": "&#9251;",
    "KC_ESC": "&#9099;",
    "KC_PGUP": "&#8670;",
    "KC_UP": "&#9650;",
    "KC_BSPC": "&#9003;",
    "KC_TAB": "&#8677;",
    "KC_PGDN": "&#8671;",
    "KC_LEFT": "&#9664;",
    "KC_DOWN": "&#9660;",
    "KC_RGHT": "&#9654;",
    "KC_ENT": "&#9166;",
    "KC_SCLN": ";",
    "KC_LPRN": "(",
    "KC_RPRN": ")",
    "KC_BSLS": "\\",
    "KC_MINS": "-",
    "KC_ASTR": "*",
    "KC_EQL": "=",
    "KC_EXLM": "&#33;",
    "KC_AT": "&#64;",
    "MY_AT": "&#64;",
    "KC_CAPS": "CapsWd",  #"&#20;",
    "KC_SNAKE": "SnakeCs",
    "KC_CAMEL": "CamelCs",
    "KC_NUMWD": "NumWord",
    "KC_HASH": "&#35;",
    "MY_GBP": "&#163;",
    "KC_DLR": "&#36;",
    "KC_PERC": "&#37;",
    "KC_PIPE": "&#124;",
    "MY_PIPE": "&#124;",
    "KC_COLN": "&#58;",
    "KC_TILD": "&#126;",
    "MY_TILD": "&#126;",
    "KC_LT": "&#60;",
    "KC_GT": "&#62;",
    "GBPD": "&#163;",
    "KC_AMPR": "&#38;",
    "KC_UNDS": "&#95;",
    "PMIN": "&#177;",
    "KC_CIRC": "&#94;",
    "KC_PLUS": "&#43;",
    "KC_LBRC": "[",
    "KC_RBRC": "]",
    "KC_LCBR": "{",
    "KC_RCBR": "}",
    "KC_GRV": "`",
    "KC_QUES": "?",
    "KC_LCTL": "&#94;",
    "OSM_SFT": "&#8679;",
    "OSM_CTL": "&#94;",
    "OSM_ALT": "&#8997;",
    "KC_LALT": "&#8997;",
    "ALT_TAB": "&#8997;&#8677;",
    "OSM_GUI": "&#8984;",
    "KC_LGUI": "&#8984;",
    "SFT_SPC": "&#9251;",
    "CTL_SPC": "&#9251;",
    "MOV_SPC": "&#9251;",
    "CTL_BSP": "&#9003;",
    "SFT_BSP": "&#9003;",
    "CTL_W": "W",
    "CTL_Y": "Y",
    "CTL_Z": "Z",
    "CTL_SLS": "/",
    "SFT_Z": "Z",
    "SFT_SLS": "/",
    "SFT_QUO": "'",
    "MY_LLCK": "Lock",
    "KC_NUBS": "\\",
    "KC_NUHS": "#",
    "MY_COMP": "Compose",
    "TO(LCMK)": "To CMK",
    "TO(LQWE)": "To QWE",
    "KC_MS_U": "&#8607;",
    "KC_MS_D": "&#8609;",
    "KC_MS_L": "&#8606;",
    "KC_MS_R": "&#8608;",
    "KC_WH_D": "&#8635;",
    "KC_WH_U": "&#8634;",
}

key_names.update(
    {k: 'Sym' for k in _layer_keys('LSYM')}
)

key_names.update(
    {k: 'Num' for k in _layer_keys('LNUM')}
)


def extract_layer_data(args):
    """extract the layer data from the keymap file specified in the args.

    returns an oredered dict of the layer name (as it appears in the keymap.c) to the data.
    """
    with open(args.keymap, 'r') as keymapfile:
        keymap_c = keymapfile.read()

    keymap_re= re.compile(
        r'const uint16_t PROGMEM keymaps\[\]\[MATRIX_ROWS\]\[MATRIX_COLS\] *= *\{(?P<keymap>[^}]*)',
        re.MULTILINE | re.DOTALL
    )
    keymap_section = keymap_re.search(keymap_c)
    if keymap_section is None:
        raise ValueError(f'could not extract keymap data from {args.keymap}')

    layer_re= re.compile(
        r' *\[(?P<layer>[A-Z_]*)\][^\n]*(?P<layout>.*?)\n *\),',
        re.MULTILINE | re.DOTALL
    )

    comment_re = re.compile(r'^ *\/\/')
    ret = OrderedDict()

    for layer_section in layer_re.finditer(keymap_section.group('keymap')):
        layer_name = layer_section.group('layer')
        layer_details = []
        for line in layer_section.group('layout').split('\n'):
            if line and not comment_re.match(line):
                # strip any trailing commas so the split does not add a blank
                keys = line.replace(' ', '').rstrip(',').split(',')
                layer_details.append(keys)

        ret[layer_name] = layer_details

    return ret


def calculate_layer_dimensions(args, keymap):
    first_layer_data = next(iter(keymap.values()))
    num_cols = calculate_num_cols(first_layer_data)
    num_rows = len(first_layer_data)

    width = num_cols * (SVG.key_spacing + SVG.key_width)
    # add the split spacing if needed, or another key space
    width += SVG.key_spacing if args.mono else SVG.split_spacing

    height = num_rows * (SVG.key_height + SVG.key_spacing) + SVG.key_spacing + SVG.last_row_pad

    return width, height


def _layer_y_offset(layer_index, layer_height):
    # note that the last layer spacing was not originally included.. if you change this work on _svg_layer_height too
    y = SVG.diagram_inset + layer_index * (layer_height + SVG.layer_title_height + SVG.layer_title_spacing + SVG.layer_spacing)
    return y


def _svg_layer_height(num_layers, layer_height):
    """the height of the layer part of the svg."""
    # add the inset top/bottom, height for each title, layer and layer spacing
    #svg_height = (2 * SVG.diagram_inset)
    #svg_height += num_layers * (SVG.layer_title_height + SVG.layer_title_spacing + layer_height + SVG.layer_spacing)
    svg_height = SVG.diagram_inset + _layer_y_offset(num_layers, layer_height)
    return svg_height


def _svg_height(num_layers, layer_height, num_compose, num_compose_groups):
    """the total height of the svg"""
    svg_height = _svg_layer_height(num_layers, layer_height)
    # now add in the compose mappings
    svg_height += num_compose * (SVG.key_spacing + SVG.key_height) + 2 * num_compose_groups * (SVG.layer_title_spacing + SVG.layer_title_height)
    return svg_height


def create_svg_header(layer_width, layer_height, num_layers, num_compose, num_compose_groups):
    svg_height = _svg_height(num_layers, layer_height, num_compose, num_compose_groups)
    svg_width = (2 * SVG.diagram_inset) + layer_width

    svg_raw = svg_header_template.substitute({
        'svg_width': svg_width,
        'svg_height': svg_height,
        'key_width': SVG.key_width,
        'key_height': SVG.key_height,
        'key_radius': SVG.key_radius,
        'held_css_class': SVG.held_css_class,
        'mods_css_class': SVG.mods_css_class,
        'blank_css_class': SVG.blank_css_class,
        'transparent_css_class': SVG.transparent_css_class,
        'layer_bg_width': layer_width,
        'layer_bg_height': layer_height,
    })
    return svg_raw


def valid_keys_in_row(row):
    # we strip out XXXXXXX records as they show keys not present, rather than
    # KC_NO which is a present key with no action
    return list(filter(lambda x: x != 'XXXXXXX', row))


def calculate_num_cols(layer_data):
    max_cols = 0
    for row in layer_data:
        max_cols = max(max_cols, len(valid_keys_in_row(row)))
    return max_cols


def create_svg_for_layer(args, layer_name, layer_data, layer_index, base_layer, layer_width, layer_height):
    """create the svg data for layer of the keymap

    :param args: the program args
    :param str layer_name: the name of this layer
    :param list[list] layer_data: the data for the whole layer, a list of rows where each row is
        a list of key names.
    :param int layer_index: the number of the layer (for positioning)
    :param list[list] base_layer: the base layer keymap, needed to look up transparent keys.
    """
    # work out how far down we are for this layer
    y = _layer_y_offset(layer_index, layer_height)
    x = SVG.diagram_inset

    # show the title
    layer_title = LAYER_DISPLAY_NAMES[layer_name]
    # SVG boxes are positioned at their centre point
    layer_title_y = y + SVG.layer_title_height / 2.0
    svg_width = (2 * SVG.diagram_inset) + layer_width
    layer_title_x = svg_width / 2.0
    svg_raw = svg_layer_title_template.substitute({
        'layer_title_x': layer_title_x,
        'layer_title_y': layer_title_y,
        'layer_title': layer_title,
    })

    y += SVG.layer_title_height + SVG.layer_title_spacing

    # and the layer background
    svg_raw += svg_layer_bg_template.substitute({
        'key_radius': SVG.key_radius,
        'layer_bg_x': x,
        'layer_bg_y': y,
    })

    y += SVG.key_spacing
    x += SVG.key_spacing

    num_cols = calculate_num_cols(layer_data)
    i=0
    for row, base_row in zip(layer_data[:-1], base_layer[:-1]):
        svg_raw += create_svg_for_row(args, row, num_cols, layer_name, x, y, base_row)
        y += (SVG.key_spacing + SVG.key_height)

    # for the last item we want extra y padding
    y += SVG.last_row_pad
    svg_raw += create_svg_for_row(args, layer_data[-1], num_cols, layer_name, x, y, base_layer[-1])

    return svg_raw


def create_svg_for_row(args, row, num_cols, layer_name, x, y, base_row):
    """create the svg data for one row of the keymap.

    :param args: the program args
    :param list row: the list of key names from the keymap
    :param int num_cols: how many columns the whole keymap has
    :param str layer_name: the name of this layer
    :param int x: the starting x position for the row
    :param int y: the starting y position for the row
    :param list[list] base_row: the base layer keymap, needed to look up transparent keys.
    """
    keys = valid_keys_in_row(row)
    # assumption of symmetry here
    padding = (num_cols - len(keys)) // 2
    assert padding >= 0

    svg_raw = ''

    x += padding * (SVG.key_width + SVG.key_spacing)

    for idx, key in enumerate(keys, padding):
        key_classes = []
        # for transparent keys look up on the base layer
        if key in (transparent_keycodes):
            key_classes.append(SVG.transparent_css_class)
            key = base_row[idx-padding]

        if key == keycode_blank:
            key_classes.append(SVG.blank_css_class)

        # get the key label, defaulting to the part after KC_
        key_label = key_names.get(key, key.removeprefix(keycode_prefix))

        # CSS classes to apply to the key
        key_is_held = key in LAYER_HELD_KEYCODES.get(layer_name, '')
        annotation = ''
        if key_is_held:
            key_classes.append(SVG.held_css_class)
            annotation = '<div class="annotation layer">held</div>'
        elif key in MODS_HELD_KEYCODES:
            key_classes.append(SVG.mods_css_class)
            annotation = f'<div class="annotation layer">{MODS_HELD_KEYCODES[key]}</div>'
        else:  # get the annnotation
            for antype, keys in annotation_keycodes.items():
                if key in keys:
                    annotation = f'<div class="annotation {antype}">{antype}</div>'

        svg_raw += svg_key_template.substitute({
            'key_radius': SVG.key_radius,
            'key_x': x,
            'key_y': y,
            'key_classes': ' '.join(key_classes),
            'key_width': SVG.key_width,
            'key_height': SVG.key_height,
            'key_label': key_label,
            'annotation': annotation,
        })

        # move to next key
        x += SVG.key_width + SVG.key_spacing
        # handling the split if needs be
        if not args.mono and (idx +1)== num_cols / 2:
            x += SVG.split_spacing

    return svg_raw


################################################################################
# this section handles the combo keys.  
################################################################################
def extract_combo_keys(keymap_str):
    """take the combo key presses from the keymap and return as a dict"""
    keys_re = re.compile(r'PROGMEM (?P<name>[^[]*)\[\]\s*=\s*\{(?P<keys>.*)COMBO_END')

    result = {}
    for combo_keys in keys_re.finditer(keymap_str):
        keys = tuple(filter(None, combo_keys.group('keys').replace(' ', '').split(',')))
        result[combo_keys.group('name')] = keys

    return result


def extract_combo_actions(keymap_str):
    """take the combo actions from the keymap and return as a dict."""
    action_re = re.compile(r'COMBO\((?P<name>[^,]*),\s*(?P<action>.*)\),')
    result = {}
    for combo_action in action_re.finditer(keymap_str):
        result[combo_action.group('name')] = combo_action.group('action')

    return result


def extract_combo_mapping(args):
    """extract the mapping of the keys pressed to the action taken"""
    with open(args.keymap, 'r') as keymap_file:
        keymap_c = keymap_file.read()

    keys = extract_combo_keys(keymap_c)
    actions = extract_combo_actions(keymap_c)

    result = {}
    for name, keys in keys.items():
        result[keys] = actions[name]

    return result


def _svg_for_adjacent_combo(keys, action, layer_idx, layer_height, row_idx, key_idx, split):

    # get the y from the layer_idx and row_idx
    y = _layer_y_offset(layer_idx, layer_height)
    y += SVG.layer_title_height + SVG.layer_title_spacing
    y += SVG.key_spacing
    y += row_idx * (SVG.key_spacing + SVG.key_height)
    # get the x from the key_idx
    x = SVG.diagram_inset
    x += SVG.key_spacing
    x += key_idx * (SVG.key_width + SVG.key_spacing)
    if key_idx > split:
        x += 0.5 * (SVG.key_width + SVG.key_spacing) + SVG.key_spacing

    action = key_names.get(action, action.removeprefix(keycode_prefix))

    svg_raw = '<g>' 
    x += 49
    y += 1
    svg_raw += f'<rect x="{x}" y="{y}" width="33" height="20" fill="#3399ff" rx="6" style="opacity:0.8"></rect>'
    x += 17
    y += 11
    svg_raw += f'<text x="{x}" y="{y}" class="combo-font">{action}</text>'
    svg_raw += '</g>'
    return svg_raw

def create_svg_for_adjacent_combo(args, layer_data, layer_height, layer_idx):
    """create the svg for the combo keys that are (horizontally) adjacent and can be shown on 
    the layer (easily)"""
    combo_mapping = extract_combo_mapping(args)

    svg_raw = ''

    for keys, action in combo_mapping.items():
        if len(keys) != 2:
            continue   # TODO work out how to show triples better...

        # look for adjacent keys on the keymap
        for row_idx, row in enumerate(layer_data):
            # know where the split is so we dont count items over the split as adjacent
            split = len(row) if args.mono else len(row) / 2

            if keys[0] in row:
                key_idx = row.index(keys[0])
                next_idx = key_idx + 1
                if next_idx == split:
                    continue  # we are at the split point
                # guard against the end of the row
                if next_idx < len(row) and row[next_idx] == keys[1]:
                    svg_raw += _svg_for_adjacent_combo(keys, action, layer_idx, layer_height, row_idx, key_idx, split)

    return svg_raw


""" examples - prev key x=606, y=44

  <g>
    <rect x="201" y="50" width="33" height="20" fill="#3399ff" rx="3" style="opacity:0.8"></rect>
    <text x="218" y="61" class="combo-font">Esc</text>
  </g>
"""


################################################################################
# end of combo section
################################################################################

################################################################################
# this section handles the compose mappings.  should be in a different file
# but there is a desire to keep this script contained..
################################################################################
def extract_compose_mappings(args):
    """take the compose key presses from the keymap and return as a dict"""
    with open(args.keymap, 'r') as keymapfile:
        keymap_c = keymapfile.read()

    compose_mapping_re = re.compile(
        r'compose_mapping\(uint16_t\* [^,]*, uint8_t [^)]*\)\s*\{(?P<mappings>.*?)COMPOSE_ERROR',
        re.MULTILINE | re.DOTALL
    )

    compose_mapping = compose_mapping_re.search(keymap_c)
    return compose_mapping.group('mappings')

def extract_compose_section(compose_text):
    """yield a generator for each compose section with the section title and the section"""
    # here we expect sections to start with a /*...*/ block and end with the next one
    # having problems with regex so process the lines directly
    in_section_name = ''
    seen_section_start = False  # have we seen the start to the section
    compose_block = []

    section_start_re = re.compile(r'\s*\/\*')
    section_end_re = re.compile(r'\s*\*+\/')
    section_name_re = re.compile(r'\s*\*\s*(?P<name>.*)\s*')

    for line in compose_text.split('\n'):
        if in_section_name:
            if section_start_re.search(line):
                # start of the next section so return the set so far
                yield in_section_name, '\n'.join(compose_block)
                in_section_name = ''
                compose_block = []
                seen_section_start = True
            elif section_end_re.search(line):
                continue  # this is the closing comment for the section header
            else:
                compose_block.append(line)
        else:
            if seen_section_start:
                seen_section_start = False
                m = section_name_re.search(line)
                if m:
                    in_section_name = m.group('name')
                else:
                    raise Exception(f"oops {line=} is supposed to be a section name")

            else:
                if section_start_re.search(line):
                    seen_section_start = True

    # yield the last block
    if compose_block:
        yield in_section_name, '\n'.join(compose_block)

    # had a failed attempt at the above with the following regex...
    # did not return all the sections
    # r'\/\*+\s*\n\s*\*\s*(?P<section_title>.*?)(?P<throw>\n\s*\*+\/\n)(?P<compose_items>[^*]*)'


def extract_compose_keys(compose_section):
    """for a section of compose keys extract each returning a generator of tuple
    (press keys), (action keys)"""
    compose_mapping_defn_re = re.compile(
        # working without the comment...
        #r'COMPOSE_MAPPING\(.*?COMPOSE_INPUT\((?P<keys>[^)]*)\),.*?\{\s*(?P<action>[^}]*);\s*\}',
        r'//\s*(?P<comment>[^\n]*)$\s*COMPOSE_MAPPING\(.*?COMPOSE_INPUT\((?P<keys>[^)]*)\),.*?\{\s*(?P<action>[^}]*);\s*\}',
        re.MULTILINE | re.DOTALL
    )

    for mapping in compose_mapping_defn_re.finditer(compose_section):
        keys = tuple(mapping.group('keys').replace(' ', '').split(','))
        action = extract_compose_action(mapping.group('action'))
        yield keys, action, mapping.group('comment')


def _send_string_to_keypresses(ss):
    ret = []
    for item in ss:
        if item == 'SS_TAP':
            continue  # dont need this in the picture
        if item.startswith('SS_'):
            ret.append(item.replace('SS_', 'KC_'))
        else:
            # we are at the end here, mods captured - need to extract the final presses
            item = item.strip('")\'')
            if item.startswith('X_'):
                ret.append(item.replace('X_', 'KC_'))
                return ret
            else:
                # need to handle C(S("ac")) meaning C+S+a then C+S+c
                rtn = []
                for key in item:
                    rtn.extend(ret)
                    rtn.append(key)
                    rtn.append(',')  # use a comma to indicate the separation
                return rtn[:-1]  # dont need the trailing comma

    return ret

def extract_compose_action(action_text):
    """turn the action like SEND_STRING / tap_code to the sequence of key presses."""
    if action_text.startswith(('caps_word', 'toggle_caps')):
        return ['KC_CAPS']

    if action_text.startswith(('toggle_num_word')):
        return ['KC_NUMWD']

    if action_text.startswith('enable_xcase_with(KC_UNDS)'):
        return ['KC_SNAKE']

    if action_text.startswith('enable_xcase_with(OSM(MOD_LSFT))'):
        return ['KC_CAMEL']

    if action_text.startswith('enable_xcase_with(KC_SLSH)'):
        return ['KC_PATH']

    tap_code_re = re.compile(r'tap_code\s*\(\s*(?P<key>[^\s]*)\)')
    m = tap_code_re.match(action_text)
    if m:  # tap code so just return the key
        return [m.group('key')]

    # now we just support SEND_STRING, as we have minimal usage now just support what we use
    ss_code_re = re.compile(r'SEND_STRING\s*\(\s*(?P<sequence>[^\s]*)\)')
    m = ss_code_re.match(action_text)
    if m:
        sequence = m.group('sequence')
        return _send_string_to_keypresses(sequence.split("("))

    raise ValueError(f'Do not know how to handle {action_text}.')


def _longest_compose_key(compose_data):
    longest_key = 0
    for group_name, keys_actions in compose_data.items():
        longest_key = max(longest_key, max(len(ka[0]) for ka in keys_actions))
    return longest_key

def _action_length(action_keys):
    # allow for the half width of the comma separator
    keys = len(list(filter(lambda a: a != ',', action_keys)))
    separators = len(list(filter(lambda a: a == ',', action_keys)))
    return keys + 0.5 * separators

def _longest_compose_action(compose_data):
    longest_action = 0
    for group_name, keys_actions in compose_data.items():
        longest_action = max(longest_action, max(_action_length(ka[1]) for ka in keys_actions))
    return longest_action

def _num_compose_actions(compose_data):
    return sum(map(len, compose_data.values()))

def extract_compose_data(args):
    compose = OrderedDict()
    if args.exclude_compose:
        return compose
    compose_mappings = extract_compose_mappings(args)
    for group_name, compose_code in extract_compose_section(compose_mappings):
        key_actions = list(extract_compose_keys(compose_code))
        compose[group_name] = key_actions

    return compose


def _create_svg_background(y, width, height):
    return f'<rect rx="{SVG.key_radius}" x="{SVG.diagram_inset}" y="{y}" width="{width}px" fill="#c0c0c0" height="{height}px"/>'

def create_svg_for_compose(compose_data, y, layer_width):
    svg_width = (2 * SVG.diagram_inset) + layer_width
    title_x = svg_width / 2.0

    svg_raw = ''

    longest_key = _longest_compose_key(compose_data)
    longest_action = _longest_compose_action(compose_data)

    for group_name, keys_actions in compose_data.items():
        # create a header of the group name
        y = y + SVG.layer_title_height + SVG.layer_title_spacing
        svg_raw += svg_layer_title_template.substitute({
            'layer_title_x': title_x,
            'layer_title_y': y + SVG.layer_title_height / 2.0,
            'layer_title': 'compose mappings: ' + group_name,
        })
        y = y + SVG.layer_title_height + SVG.layer_title_spacing

        height = len(keys_actions) * (SVG.key_height + SVG.key_spacing)
        svg_raw += _create_svg_background(y, layer_width, height)

        for keys, actions, comment in keys_actions:
            x = SVG.diagram_inset

            for k in keys:
                svg_raw += svg_key_template.substitute({
                    'key_radius': SVG.key_radius,
                    'key_x': x,
                    'key_y': y,
                    'key_classes': ' ',
                    'key_width': SVG.key_width,
                    'key_height': SVG.key_height,
                    'key_label': key_names.get(k, k.removeprefix(keycode_prefix)),
                    'annotation': '',
                })
                # move to next key
                x += SVG.key_width + SVG.key_spacing

            # padding to longest key length
            x += (SVG.key_width + SVG.key_spacing) * (longest_key - len(keys))
            # add a half key separator
            x += 0.5 * (SVG.key_width + SVG.key_spacing)

            for a in actions:
                if a == ',':  # the , is a split between actions so leave blank
                    x += (SVG.key_width + SVG.key_spacing) / 2
                else:
                    svg_raw += svg_key_template.substitute({
                        'key_radius': SVG.key_radius,
                        'key_x': x,
                        'key_y': y,
                        'key_classes': '',
                        'key_width': SVG.key_width,
                        'key_height': SVG.key_height,
                        'key_label': key_names.get(a, a.removeprefix(keycode_prefix)),
                        'annotation': '',
                    })
                    # move to next key
                    x += SVG.key_width + SVG.key_spacing

            # add the comment
            text_y = y + 0.5 * (SVG.key_width + SVG.key_spacing)
            action_width = longest_action * (SVG.key_width + SVG.key_spacing)
            text_x = action_width + (layer_width - action_width) / 2
            svg_raw += f'<text x="{text_x}px" y="{text_y}">{comment}</text>'

            y += SVG.key_spacing + SVG.key_height

    return svg_raw

################################################################################
# end of compose code...
################################################################################

def create_and_write_svg(args):
    """do the work..."""
    keymap = extract_layer_data(args)
    compose_data = extract_compose_data(args)
    first_layer_data = next(iter(keymap.values()))

    # get the layer dimensions for layout
    layer_width, layer_height = calculate_layer_dimensions(args, keymap)
    num_layers = 1 if args.layer else len(keymap)
    # and the number of compose
    num_compose = _num_compose_actions(compose_data)
    num_compose_groups = len(compose_data)

    svg_header = create_svg_header(layer_width, layer_height, num_layers, num_compose, num_compose_groups)
    svg_for_layers = []
    base_layer = None
    layer_idx = 0
    for layer_name, layer_data in keymap.items():
        base_layer = base_layer or layer_data  # save the first layer
        if args.layer and layer_name != args.layer:
            continue
        svg_for_layers.append(create_svg_for_layer(args, layer_name, layer_data, layer_idx, base_layer, layer_width, layer_height))
        svg_for_layers.append(create_svg_for_adjacent_combo(args, layer_data, layer_height, layer_idx))
        layer_idx += 1

    y = _layer_y_offset(num_layers, layer_height)
    svg_compose = ''
    if not args.exclude_compose:
        svg_compose = create_svg_for_compose(compose_data, y, layer_width) # assume layer is widest bit

    with open(args.output, 'w') as svg_file:
        svg_file.write(svg_header)
        for svgl in svg_for_layers:
            svg_file.write(svgl)

        svg_file.write(svg_compose)

        svg_file.write(svg_footer)


def main():
    parser = argparse.ArgumentParser(description='Generate a keymap diagram.')
    parser.add_argument(
        '-k',
        '--keymap',
        type=str,
        nargs='?',
        default='keymap.c',
        help='the name of the keymap file to parse.'
    )
    parser.add_argument(
        '-o',
        '--output',
        type=str,
        nargs='?',
        default='keymap_diagram.svg',
        help='the name of the output svg file to create.'
    )
    parser.add_argument(
        '-l',
        '--layer',
        type=str,
        nargs='?',
        default='',
        help='create a file for the single layer (default is all)'
    )
    parser.add_argument(
        '-m',
        '--mono',
        action='store_true',
        default=False,
        help='is the keyboard a mono board or split (default)'
    )
    parser.add_argument(
        '-x',
        '--exclude_compose',
        action='store_true',
        default=False,
        help='should the compose mappings be added to the bottom of the diagram'
    )

    args = parser.parse_args()

    create_and_write_svg(args)


if __name__ == "__main__":
    main()
