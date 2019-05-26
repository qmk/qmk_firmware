import json
import logging
import os
from traceback import format_exc

from .errors import NoSuchKeyboardError

# The `keymap.c` template to use when a keyboard doesn't have its own
DEFAULT_KEYMAP_C = """#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
__KEYMAP_GOES_HERE__
};
"""


# Helper Functions
def find_dir(keyboard):
    """Locate the correct directory for storing a keymap.
    """
    for directory in ['.', '..', '../..', '../../..', '../../../..', '../../../../..']:
        basepath = os.path.normpath(os.path.join('keyboards', keyboard, directory, 'keymaps'))
        if os.path.exists(basepath):
            return basepath

    logging.error('Could not find keymaps directory!')
    raise NoSuchKeyboardError('Could not find keymaps directory for: %s' % keyboard)


def template(keyboard, keymap):
    """Returns the `keymap.c` template for a keyboard.

    If a template exists in `keyboards/<keyboard>/templates/keymap.c` that
    text will be used instead of `DEFAULT_KEYMAP_C`.
    """
    template_name = 'keyboards/%s/templates/keymap.c' % keyboard

    if os.path.exists(template_name):
        with open(template_name, 'r') as fd:
            template_text = fd.read()

    return DEFAULT_KEYMAP_C.replace('__KEYMAP_GOES_HERE__', keymap)

    
def generate(keyboard, layout, layers):
    """Generate the keymap source code.
    """
    layer_txt = []
    for layer_num, layer in enumerate(layers):
        if layer_num != 0:
            layer_txt[-1] = layer_txt[-1] + ','
        layer_keys = ', '.join(layer)
        layer_txt.append('\t[%s] = %s(%s)' % (layer_num, layout, layer_keys))

    keymap = '\n'.join(layer_txt)
    keymap_c = template(keyboard, keymap)

    return keymap_c


def write(keyboard, layout, layers):
    """Generate the `keymap.c` and write it to disk.
    """
    keymap_c = generate(keyboard, layout, layers)
    keymap_path = find_dir(keyboard)
    keymap_file = os.path.join(keymap_path, 'keymap.c')

    with open(keymap_file, 'w') as keymap_fd:
        keymap_fd.write(keymap_c)

    return keymap_file


# Public functions
def compile_firmware(keyboard, keymap, layout, layers):
    """Compile a firmware.
    """
    result = {
        'keyboard': keyboard,
        'layout': layout,
        'keymap': keymap,
        'command': ['make', 'COLOR=false', ':'.join((keyboard, keymap))],
        'returncode': -2,
        'output': '',
        'firmware': None,
        'firmware_filename': ''
    }

    try:
        job = get_current_job()
        result['id'] = job.id
        checkout_qmk()

        # Sanity checks
        if not os.path.exists('qmk_firmware/keyboards/' + keyboard):
            logging.error('Unknown keyboard: %s', keyboard)
            return {'returncode': -1, 'command': '', 'output': 'Unknown keyboard!', 'firmware': None}

        for pathname in ('qmk_firmware/keyboards/%s/keymaps/%s' % (keyboard, keymap),
                         'qmk_firmware/keyboards/%s/../keymaps/%s' % (keyboard, keymap)):
            if os.path.exists(pathname):
                logging.error('Name collision! %s already exists! This should not happen!', pathname)
                return {'returncode': -1, 'command': '', 'output': 'Keymap name collision! %s already exists!' % (pathname), 'firmware': None}

        # Build the keyboard firmware
        write_keymap(result['keyboard'], result['keymap'], layers)
        store_firmware_binary(result)

    except Exception as e:
        result['returncode'] = -3
        result['exception'] = e.__class__.__name__
        result['stacktrace'] = format_exc()

        if not result['output']:
            result['output'] = result['stacktrace']

    return result
