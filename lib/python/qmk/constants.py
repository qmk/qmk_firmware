"""Information that should be available to the python library.
"""
from os import environ
from pathlib import Path

# The root of the qmk_firmware tree.
QMK_FIRMWARE = Path.cwd()

# Upstream repo url
QMK_FIRMWARE_UPSTREAM = 'qmk/qmk_firmware'

# This is the number of directories under `qmk_firmware/keyboards` that will be traversed. This is currently a limitation of our make system.
MAX_KEYBOARD_SUBFOLDERS = 5

# Common format strings
DATE_FORMAT = '%Y-%m-%d'
DATETIME_FORMAT = '%Y-%m-%d %H:%M:%S %Z'
TIME_FORMAT = '%H:%M:%S'

# Used when generating matrix locations
COL_LETTERS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijilmnopqrstuvwxyz'
ROW_LETTERS = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnop'

# Mapping between info.json and config.h keys
LED_INDICATORS = {
    'caps_lock': 'LED_CAPS_LOCK_PIN',
    'num_lock': 'LED_NUM_LOCK_PIN',
    'scroll_lock': 'LED_SCROLL_LOCK_PIN',
}

# Constants that should match their counterparts in make
BUILD_DIR = environ.get('BUILD_DIR', '.build')
KEYBOARD_OUTPUT_PREFIX = f'{BUILD_DIR}/obj_'
