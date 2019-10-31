from enum import auto, Flag
import itertools
import json
import os
from pathlib import Path
from typing import List, NamedTuple

from milc import cli
import pycparser
from pycparser.c_ast import BinaryOp, Constant, Decl, ID
from pycparserext.ext_c_parser import GnuCParser


def iter_upwards(path):
    """
    Generator to iterate through all parent directories yielding a Path
    for each

    Parameters:
    path -- Path object to walk through
    """
    parts = list(path.resolve().parts)
    while parts:
        yield Path(*parts)
        parts.pop()


def find_topmost_keyboard_h(path):
    """
    Look through all directories up from the given path to find a keyboard.h
    file. This is used for resolving QMK_KEYBOARD_H.

    Parameters:
    path -- path to the keymap.h we are resolving for

    Returns:
    A Path object for the keyboard.h found or None if we can't find one

    Signature:
    (path: Path) -> Path
    """

    def header_name(directory: Path) -> str:
        return directory.name + '.h'

    # path will look like
    # keyboards/NAME/SUBNAME/keymaps/keymap.c
    keyboard_h = None
    for part in iter_upwards(path):
        # if we hit a root level subdirectory we've overshot it
        if part.name in ('keyboards', 'users', 'layouts'):
            return keyboard_h

        header = part / header_name(part)
        if header.exists():
            keyboard_h = header


def get_qmk_root(from_path):
    """
    Finds the path of the QMK repository root relative to a keymaps directory

    Parameters:
    from_path -- Path to find the QMK root relative to

    Signature:
    (from_path: Path) -> Path
    """
    for part in iter_upwards(from_path.absolute()):
        if (part / 'keyboards').exists():
            return part


def recursive_subdirs(from_path):
    """
    Generator that walks down the filesystem tree and gets all subdirectories
    under the Path ``from_path``

    Parameters:
    from_path -- Path to walk from
    """
    yield from_path
    for dirpath, dirs, files in os.walk(from_path):
        yield from (Path(dirpath) / d for d in dirs)


def parse_keymap_c(path):
    """
    Loads a C AST from the given keymap.c file.

    Parameters:
    path -- Path of the keymap.c to parse
    """
    qmk_root = get_qmk_root(path)
    keyboard_h = find_topmost_keyboard_h(path)

    # I'm guessing make probably doesn't just put the entire source tree as
    # an include path??
    def subdir_includes(parent: Path):
        return (f'-I{parent / d}' for d in recursive_subdirs(parent))

    # we need to use the GNU C parser so attributes in system headers and
    # other inconvenient things don't cause our parse to fail
    return pycparser.parse_file(
        str(path),
        parser=GnuCParser(),
        use_cpp=True,
        cpp_args=[
            f'-DQMK_KEYBOARD_H="{keyboard_h}"',
            '-std=gnu99',
            *subdir_includes(keyboard_h.parent),
            *subdir_includes(qmk_root / 'quantum'),
            *subdir_includes(qmk_root / 'tmk_core'),
        ]
    )


def find_keymaps_in_ast(ast):
    """
    Finds the keymaps object inside the full C AST of the keymap.c file
    """
    for node in ast.ext:
        if type(node) != Decl:
            continue
        # we need to check if it is 'extern' to avoid parsing the extern
        # declaration of keymaps within the QMK source itself
        if node.name == 'keymaps' and 'extern' not in node.storage:
            return node
    return None


Key = str

class Layer(NamedTuple):
    name: str
    keys: List[List[Key]]


MODIFIER_MAP = {
    'QK_LSFT': 'LSFT',
    'QK_LCTL': 'LCTL',
    'QK_LALT': 'LALT',
    'QK_LGUI': 'LGUI',
    'QK_RSFT': 'RSFT',
    'QK_RCTL': 'RCTL',
    'QK_RALT': 'RALT',
    'QK_RGUI': 'RGUI',
}


def or_ast_to_modifiers(or_ast, log):
    """
    Turns an AST of binary OR operations into modifiers.

    Returns: (modifiers list, key) tuple

    Example input:
    >>> or_ast_to_modifiers(
    ... BinaryOp(op='|',
    ...          left=BinaryOp(op='|',
    ...                        left=BinaryOp(op='|',
    ...                                      left=ID(name='QK_LCTL'
    ...                                              ),
    ...                                      right=ID(name='QK_LSFT'
    ...                                               )
    ...                                      ),
    ...                        right=ID(name='QK_LALT'
    ...                                 )
    ...                        ),
    ...          right=ID(name='KC_A'
    ...                   )
    ...          ))
    (['LALT', 'LSFT', 'LCTL'], 'KC_A')
    """

    log.debug('handling operation AST: %r', or_ast)
    queue = [or_ast]
    keycodes = []
    # stage 1: traverse the tree and pull out all the keycodes
    while queue:
        item = queue.pop()
        if type(item) == ID:
            keycodes.append(item.name)
        elif type(item) == BinaryOp:
            if item.op != '|':
                log.warn('Encountered non-OR binary operation in your keymap! %r', item)
                continue
            queue.append(item.left)
            queue.append(item.right)

    # stage 2: separate these into modifiers and keycodes
    modifiers = []
    keycode = None
    for kc in keycodes:
        if kc in MODIFIER_MAP:
            modifiers.append(MODIFIER_MAP[kc])
        else:
            keycode = kc
    return (modifiers, keycode)


def make_modifier_keycode(modifiers, keycode):
    """
    Turns a list of modifiers into parenthesized form

    Parameters:
    modifiers -- List[str] of modifiers
    keycode -- string keycode to apply them to

    Example:
    >>> make_modifier_keycode(['LALT', 'LSFT', 'LCTL'], 'KC_A')
    'LCTL(LSFT(LALT(KC_A)))'
    """
    result = keycode
    for modifier in modifiers:
        result = '{}({})'.format(modifier, result)
    return result


def extract_row(row_ast, log):
    """
    Extracts a row as a List[Key] of keycode strings

    Transforms an InitList of keycode ASTs into a list of string QMK keycodes
    """
    # each layer is a
    # InitList of rows ->
    #   InitList of IDs or more complex objects
    row = []
    for expr in row_ast.exprs:
        if type(expr) == ID:
            row.append(expr.name)
        elif type(expr) == Constant and expr.type == 'int':
            if expr.value != '0x01':
                # KC_TRNS is represented by 0x01
                log.warn('Discarding an unrecognized numeric keycode: %s', expr.value)
            row.append('KC_TRNS')
        elif type(expr) == BinaryOp:
            # it's probably a modifier set
            modifiers, keycode = or_ast_to_modifiers(expr, log=log)
            row.append(make_modifier_keycode(modifiers, keycode))
        else:
            log.warn('Not implemented: emitting KC_TRNS for %s', expr)
            row.append('KC_TRNS')
            continue
    return row


def extract_layers(keymaps, log):
    """
    Takes an AST representation of the keymaps array and pulls the layers out
    as Layer objects

    Returns:
    List[Layer] representing the layers in the AST
    """
    layers = []
    for layer in keymaps.init.exprs:
        name = layer.name[0].value
        rows_ast = layer.expr.exprs
        rows = []
        for row_ast in rows_ast:
            rows.append(extract_row(row_ast, log=log))
        layers.append(Layer(name=name, keys=rows))
    return layers


def find_keyboard_name_from_keymap_c(keymap_c):
    """
    Takes the path to a keymap.c and divines the keyboard name.

    Parameters:
    keymap_c -- Path object representing the keymap.c file

    >>> find_keyboard_name_from_keymap_c(Path('keyboards/clueboard/66/keymaps/default/keymap.c'))
    'clueboard/66'
    """
    parts = keymap_c.parts
    return '/'.join(parts[(parts.index('keyboards') + 1) : parts.index('keymaps')])


def make_keymap_json(keymap_c, layer_list):
    """
    Converts a list of our internal Layer objects to a JSON dictionary
    suitable for the configurator.

    Parameters:
    keymap_c -- Path representing the location of the keymap.c
    layer_list -- List[Layer]
    """
    flatten_list = lambda lst: list(itertools.chain.from_iterable(lst))

    obj = {
        'keyboard': find_keyboard_name_from_keymap_c(keymap_c),
        'keymap': keymap_c.parent.name,
        'layout': 'KEYMAP',  # I don't know what this means
        'layers': [flatten_list(layer.keys) for layer in layer_list]
    }
    return json.dumps(obj)


def keymap_c_to_json_string(keymap_c, log):
    """
    Performs the full process of parsing a keymap.c and turning it into a JSON
    keymap file

    Parameters:
    keymap_c -- Path to the keymap.c
    """
    keymaps = find_keymaps_in_ast(parse_keymap_c(keymap_c))
    layers = extract_layers(keymaps, log=log)
    return make_keymap_json(keymap_c, layers)


@cli.argument('keymap_c', help='path to keymap.c to convert')
@cli.subcommand('Convert a keymap.c to keymap.json format')
def c2json(cli):
    """
    Convert keymap.c to keymap.json.

    FIXME(lf-): this doesn't work with TO(layer) yet
    """
    print(keymap_c_to_json_string(Path(cli.args.keymap_c), log=cli.log))

