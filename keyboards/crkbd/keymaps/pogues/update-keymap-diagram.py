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
    layer_title_spacing = 10

    held_css_class = 'held'
    mods_css_class = 'mods'
    blank_css_class = 'blank'
    transparent_css_class = 'transparent'

keycode_blank = 'NO'
transparent_keycodes = ('_______', 'KC_TRNS')

annotation_keycodes = { 
    'layer': ['TD(TD_LSYM)', 'TD(TD_LNUM)'],
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
    'LSYM': ['TD(TD_LSYM)'],
    'LNUM': ['TD(TD_LNUM)'],
    'LMOV': ['TD(TD_LSYM', 'TD(TD_LNUM)'],
}
MODS_HELD_KEYCODES = {
    # indicate which keys are dual role tap/mods
    # here we list the mods key, the tap is defined in key_names
    'CTL_BSP': 'Ctrl',
    'SFT_SPC': '&#8679;',
    'SFT_BSP': '&#8679;',
    'CTL_Z': 'Ctrl',
    'CTL_SLS': 'Ctrl',
}

keycode_prefix = 'KC_'
key_names = {
    "KC_NO": "",
    "M_UNDO": "Undo",
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
    #"OSM_ALT": "Alt",
    #"OSM_GUI": "Gui",
    #"OSM_CTL": "Ctrl",
    #"OSM_SFT": "Shft",
    "OSM_SFT": "&#8679;",
    "OSM_CTL": "&#94;",
    "OSM_ALT": "&#8997;",
    "KC_LALT": "&#8997;",
    "ALT_TAB": "&#8997;&#8677;",   #   TODO
    "OSM_GUI": "&#8984;",
    "KC_LGUI": "&#8984;",
    "TD(TD_LNUM)": "Num",
    "TD(TD_LSYM)": "Sym",
    "SFT_SPC": "&#9251;",
    "CTL_BSP": "&#9003;",
    "SFT_BSP": "&#9003;",
    "CTL_Z": "Z",
    "CTL_SLS": "/",
    "MY_LLCK": "Lock",
    "KC_NUBS": "\\",
    "KC_NUHS": "#",
    "MY_COMP": "Compose",
    "TO(LCMK)": "To CMK",
    "TO(LQWE)": "To QWE",
}


def extract_layer_data(args):
    """extract the layer data from the keymap file specified in the args.

    returns an oredered dict of the layer name (as it appears in the keymap.c)to the data.
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


def calculate_layer_dimensions(args, layer_data):
    num_cols = calculate_num_cols(layer_data)
    num_rows = len(layer_data)

    width = num_cols * (SVG.key_spacing + SVG.key_width) 
    # add the split spacing if needed, or another key space
    width += SVG.split_spacing if args.split else SVG.key_spacing

    height = num_rows * (SVG.key_height + SVG.key_spacing) + SVG.key_spacing + SVG.last_row_pad

    return width, height

def create_svg_header(args, keymap):
    first_layer_data = next(iter(keymap.values()))
    layer_width, layer_height = calculate_layer_dimensions(args, first_layer_data)
    num_layers = len(keymap)

    svg_width = (2 * SVG.diagram_inset) + layer_width
    svg_height = (2 * SVG.diagram_inset) + (num_layers * layer_height) + ((num_layers - 1) * SVG.layer_spacing)
    # add in the titles
    svg_height += num_layers * (SVG.layer_title_height + SVG.layer_title_spacing)
    
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

def create_svg_for_layer(args, layer_name, layer_data, layer_index, base_layer):
    """create the svg data for layer of the keymap

    :param args: the program args
    :param str layer_name: the name of this layer
    :param list[list] layer_data: the data for the whole layer, a list of rows where each row is
        a list of key names.
    :param int layer_index: the number of the layer (for positioning)
    :param list[list] base_layer: the base layer keymap, needed to look up transparent keys.
    """
    # work out how far down we are for this layer
    w, h = calculate_layer_dimensions(args, layer_data)
    y = SVG.diagram_inset + layer_index * (h + SVG.layer_title_height + SVG.layer_title_spacing)
    x = SVG.diagram_inset

    # show the title
    layer_title = LAYER_DISPLAY_NAMES[layer_name]
    # SVG boxes are positioned at their centre point
    layer_title_y = y + SVG.layer_title_height / 2.0
    svg_width = (2 * SVG.diagram_inset) + w
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
    # TODO assumption of symmetry here
    padding = (num_cols - len(keys)) // 2
    assert padding >= 0

    svg_raw = ''

    x += padding * (SVG.key_width + SVG.key_spacing)

    for idx, key in enumerate(keys, padding):
        key_classes = []
        # for transparent keys look up on the base layer
        if key in (transparent_keycodes):
            key_is_transparent = True
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
            # TODO
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
        if args.split and (idx +1)== num_cols / 2:
            x += SVG.split_spacing

    return svg_raw

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
        '-s',
        '--split',
        type=bool,
        nargs='?',
        default=True,
        help='is the keyboard split (default) or not'
    )

    args = parser.parse_args()

    keymap = extract_layer_data(args)
    svg_header = create_svg_header(args, keymap)
    svg_for_layers = []
    base_layer = None
    layer_idx = 0
    for layer_name, layer_data in keymap.items():
        base_layer = base_layer or layer_data  # TODO better way to get first one.
        if args.layer and layer_name != args.layer:
            continue
        svg_for_layers.append(create_svg_for_layer(args, layer_name, layer_data, layer_idx, base_layer))
        layer_idx += 1

    with open(args.output, 'w') as svg_file:
        svg_file.write(svg_header)
        for svgl in svg_for_layers:
            svg_file.write(svgl)

        svg_file.write(svg_footer)

if __name__ == "__main__":
    main()
