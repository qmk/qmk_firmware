"""Functions that help you work with QMK keymaps.
"""
from pathlib import Path
import json

from pygments.lexers.c_cpp import CLexer
from pygments.token import Token
from pygments import lex

from milc import cli

from qmk.keyboard import rules_mk
import qmk.path
import qmk.commands

# The `keymap.c` template to use when a keyboard doesn't have its own
DEFAULT_KEYMAP_C = """#include QMK_KEYBOARD_H

/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
__KEYMAP_GOES_HERE__
};
"""


def template(keyboard, type='c'):
    """Returns the `keymap.c` or `keymap.json` template for a keyboard.

    If a template exists in `keyboards/<keyboard>/templates/keymap.c` that
    text will be used instead of `DEFAULT_KEYMAP_C`.

    If a template exists in `keyboards/<keyboard>/templates/keymap.json` that
    text will be used instead of an empty dictionary.

    Args:
        keyboard
            The keyboard to return a template for.

        type
            'json' for `keymap.json` and 'c' (or anything else) for `keymap.c`
    """
    if type == 'json':
        template_file = Path('keyboards/%s/templates/keymap.json' % keyboard)
        template = {'keyboard': keyboard}
        if template_file.exists():
            template.update(json.loads(template_file.read_text()))
    else:
        template_file = Path('keyboards/%s/templates/keymap.c' % keyboard)
        if template_file.exists():
            template = template_file.read_text()
        else:
            template = DEFAULT_KEYMAP_C

    return template


def _strip_any(keycode):
    """Remove ANY() from a keycode.
    """
    if keycode.startswith('ANY(') and keycode.endswith(')'):
        keycode = keycode[4:-1]

    return keycode


def is_keymap_dir(keymap):
    """Return True if Path object `keymap` has a keymap file inside.
    """
    for file in ('keymap.c', 'keymap.json'):
        if (keymap / file).is_file():
            return True


def generate(keyboard, layout, layers, type='c', keymap=None):
    """Returns a `keymap.c` or `keymap.json` for the specified keyboard, layout, and layers.

    Args:
        keyboard
            The name of the keyboard

        layout
            The LAYOUT macro this keymap uses.

        layers
            An array of arrays describing the keymap. Each item in the inner array should be a string that is a valid QMK keycode.

        type
            'json' for `keymap.json` and 'c' (or anything else) for `keymap.c`
    """
    new_keymap = template(keyboard, type)
    if type == 'json':
        new_keymap['keymap'] = keymap
        new_keymap['layout'] = layout
        new_keymap['layers'] = layers
    else:
        layer_txt = []
        for layer_num, layer in enumerate(layers):
            if layer_num != 0:
                layer_txt[-1] = layer_txt[-1] + ','
            layer_keys = ', '.join(layer)
            layer_txt.append('\t[%s] = %s(%s)' % (layer_num, layout, layer_keys))

        keymap = '\n'.join(layer_txt)
        new_keymap = new_keymap.replace('__KEYMAP_GOES_HERE__', keymap)

    return new_keymap


def write(keyboard, keymap, layout, layers, type='c'):
    """Generate the `keymap.c` and write it to disk.

    Returns the filename written to.

    Args:
        keyboard
            The name of the keyboard

        keymap
            The name of the keymap

        layout
            The LAYOUT macro this keymap uses.

        layers
            An array of arrays describing the keymap. Each item in the inner array should be a string that is a valid QMK keycode.

        type
            'json' for `keymap.json` and 'c' (or anything else) for `keymap.c`
    """
    keymap_content = generate(keyboard, layout, layers, type)
    if type == 'json':
        keymap_file = qmk.path.keymap(keyboard) / keymap / 'keymap.json'
        keymap_content = json.dumps(keymap_content)
    else:
        keymap_file = qmk.path.keymap(keyboard) / keymap / 'keymap.c'

    keymap_file.parent.mkdir(parents=True, exist_ok=True)
    keymap_file.write_text(keymap_content)

    cli.log.info('Wrote keymap to {fg_cyan}%s', keymap_file)

    return keymap_file


def locate_keymap(keyboard, keymap):
    """Returns the path to a keymap for a specific keyboard.
    """
    if not qmk.path.is_keyboard(keyboard):
        raise KeyError('Invalid keyboard: ' + repr(keyboard))

    # Check the keyboard folder first, last match wins
    checked_dirs = ''
    keymap_path = ''

    for dir in keyboard.split('/'):
        if checked_dirs:
            checked_dirs = '/'.join((checked_dirs, dir))
        else:
            checked_dirs = dir

        keymap_dir = Path('keyboards') / checked_dirs / 'keymaps'

        if (keymap_dir / keymap / 'keymap.c').exists():
            keymap_path = keymap_dir / keymap / 'keymap.c'
        if (keymap_dir / keymap / 'keymap.json').exists():
            keymap_path = keymap_dir / keymap / 'keymap.json'

    if keymap_path:
        return keymap_path

    # Check community layouts as a fallback
    rules = rules_mk(keyboard)

    if "LAYOUTS" in rules:
        for layout in rules["LAYOUTS"].split():
            community_layout = Path('layouts/community') / layout / keymap
            if community_layout.exists():
                if (community_layout / 'keymap.json').exists():
                    return community_layout / 'keymap.json'
                if (community_layout / 'keymap.c').exists():
                    return community_layout / 'keymap.c'


def list_keymaps(keyboard):
    """ List the available keymaps for a keyboard.

    Args:
        keyboard: the keyboards full name with vendor and revision if necessary, example: clueboard/66/rev3

    Returns:
        a set with the names of the available keymaps
    """
    # parse all the rules.mk files for the keyboard
    rules = rules_mk(keyboard)
    names = set()

    if rules:
        # qmk_firmware/keyboards
        keyboards_dir = Path('keyboards')
        # path to the keyboard's directory
        kb_path = keyboards_dir / keyboard
        # walk up the directory tree until keyboards_dir
        # and collect all directories' name with keymap.c file in it
        while kb_path != keyboards_dir:
            keymaps_dir = kb_path / "keymaps"
            if keymaps_dir.exists():
                names = names.union([keymap.name for keymap in keymaps_dir.iterdir() if is_keymap_dir(keymap)])
            kb_path = kb_path.parent

        # if community layouts are supported, get them
        if "LAYOUTS" in rules:
            for layout in rules["LAYOUTS"].split():
                cl_path = Path('layouts/community') / layout
                if cl_path.exists():
                    names = names.union([keymap.name for keymap in cl_path.iterdir() if is_keymap_dir(keymap)])

    return sorted(names)


def _c_preprocess(path):
    """ Run a file through the C pre-processor

    Args:
        path: path of the keymap.c file

    Returns:
        the stdout of the pre-processor
    """
    pre_processed_keymap = qmk.commands.run(['cpp', path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    return pre_processed_keymap.stdout


def _get_layers(keymap):  # noqa C901 : until someone has a good idea how to simplify/split up this code
    """ Find the layers in a keymap.c file.

    Args:
        keymap: the content of the keymap.c file

    Returns:
        a dictionary containing the parsed keymap
    """
    layers = list()
    opening_braces = '({['
    closing_braces = ')}]'
    keymap_certainty = brace_depth = 0
    is_keymap = is_layer = is_adv_kc = False
    layer = dict(name=False, layout=False, keycodes=list())
    for line in lex(keymap, CLexer()):
        if line[0] is Token.Name:
            if is_keymap:
                # If we are inside the keymap array
                # we know the keymap's name and the layout macro will come,
                # followed by the keycodes
                if not layer['name']:
                    if line[1].startswith('LAYOUT') or line[1].startswith('KEYMAP'):
                        # This can happen if the keymap array only has one layer,
                        # for macropads and such
                        layer['name'] = '0'
                        layer['layout'] = line[1]
                    else:
                        layer['name'] = line[1]
                elif not layer['layout']:
                    layer['layout'] = line[1]
                elif is_layer:
                    # If we are inside a layout macro,
                    # collect all keycodes
                    if line[1] == '_______':
                        kc = 'KC_TRNS'
                    elif line[1] == 'XXXXXXX':
                        kc = 'KC_NO'
                    else:
                        kc = line[1]
                    if is_adv_kc:
                        # If we are inside an advanced keycode
                        # collect everything and hope the user
                        # knew what he/she was doing
                        layer['keycodes'][-1] += kc
                    else:
                        layer['keycodes'].append(kc)

        # The keymaps array's signature:
        # const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS]
        #
        # Only if we've found all 6 keywords in this specific order
        # can we know for sure that we are inside the keymaps array
            elif line[1] == 'PROGMEM' and keymap_certainty == 2:
                keymap_certainty = 3
            elif line[1] == 'keymaps' and keymap_certainty == 3:
                keymap_certainty = 4
            elif line[1] == 'MATRIX_ROWS' and keymap_certainty == 4:
                keymap_certainty = 5
            elif line[1] == 'MATRIX_COLS' and keymap_certainty == 5:
                keymap_certainty = 6
        elif line[0] is Token.Keyword:
            if line[1] == 'const' and keymap_certainty == 0:
                keymap_certainty = 1
        elif line[0] is Token.Keyword.Type:
            if line[1] == 'uint16_t' and keymap_certainty == 1:
                keymap_certainty = 2
        elif line[0] is Token.Punctuation:
            if line[1] in opening_braces:
                brace_depth += 1
                if is_keymap:
                    if is_layer:
                        # We found the beginning of a non-basic keycode
                        is_adv_kc = True
                        layer['keycodes'][-1] += line[1]
                    elif line[1] == '(' and brace_depth == 2:
                        # We found the beginning of a layer
                        is_layer = True
                elif line[1] == '{' and keymap_certainty == 6:
                    # We found the beginning of the keymaps array
                    is_keymap = True
            elif line[1] in closing_braces:
                brace_depth -= 1
                if is_keymap:
                    if is_adv_kc:
                        layer['keycodes'][-1] += line[1]
                        if brace_depth == 2:
                            # We found the end of a non-basic keycode
                            is_adv_kc = False
                    elif line[1] == ')' and brace_depth == 1:
                        # We found the end of a layer
                        is_layer = False
                        layers.append(layer)
                        layer = dict(name=False, layout=False, keycodes=list())
                    elif line[1] == '}' and brace_depth == 0:
                        # We found the end of the keymaps array
                        is_keymap = False
                        keymap_certainty = 0
            elif is_adv_kc:
                # Advanced keycodes can contain other punctuation
                # e.g.: MT(MOD_LCTL | MOD_LSFT, KC_ESC)
                layer['keycodes'][-1] += line[1]

        elif line[0] is Token.Literal.Number.Integer and is_keymap and not is_adv_kc:
            # If the pre-processor finds the 'meaning' of the layer names,
            # they will be numbers
            if not layer['name']:
                layer['name'] = line[1]

        else:
            # We only care about
            # operators and such if we
            # are inside an advanced keycode
            # e.g.: MT(MOD_LCTL | MOD_LSFT, KC_ESC)
            if is_adv_kc:
                layer['keycodes'][-1] += line[1]

    return layers


def parse_keymap_c(keymap_file, use_cpp=True):
    """ Parse a keymap.c file.

    Currently only cares about the keymaps array.

    Args:
        keymap_file: path of the keymap.c file

        use_cpp: if True, pre-process the file with the C pre-processor

    Returns:
        a dictionary containing the parsed keymap
    """
    if use_cpp:
        keymap_file = _c_preprocess(keymap_file)
    else:
        keymap_file = keymap_file.read_text()

    keymap = dict()
    keymap['layers'] = _get_layers(keymap_file)
    return keymap


def c2json(keyboard, keymap, keymap_file, use_cpp=True):
    """ Convert keymap.c to keymap.json

    Args:
        keyboard: The name of the keyboard

        keymap: The name of the keymap

        layout: The LAYOUT macro this keymap uses.

        keymap_file: path of the keymap.c file

        use_cpp: if True, pre-process the file with the C pre-processor

    Returns:
        a dictionary in keymap.json format
    """
    keymap_json = parse_keymap_c(keymap_file, use_cpp)

    dirty_layers = keymap_json.pop('layers', None)
    keymap_json['layers'] = list()
    for layer in dirty_layers:
        layer.pop('name')
        layout = layer.pop('layout')
        if not keymap_json.get('layout', False):
            keymap_json['layout'] = layout
        keymap_json['layers'].append(layer.pop('keycodes'))

    keymap_json['keyboard'] = keyboard
    keymap_json['keymap'] = keymap
    return keymap_json
