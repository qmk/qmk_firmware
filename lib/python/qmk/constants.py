"""Information that should be available to the python library.
"""
from os import environ
from datetime import date
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

# Headers for generated files
GPL2_HEADER_C_LIKE = f'''\
// Copyright {date.today().year} QMK
// SPDX-License-Identifier: GPL-2.0-or-later
'''

GPL2_HEADER_SH_LIKE = f'''\
# Copyright {date.today().year} QMK
# SPDX-License-Identifier: GPL-2.0-or-later
'''

GENERATED_HEADER_C_LIKE = '''\
/*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************/
'''

GENERATED_HEADER_SH_LIKE = '''\
################################################################################
#
# 88888888888 888      d8b                .d888 d8b 888               d8b
#     888     888      Y8P               d88P"  Y8P 888               Y8P
#     888     888                        888        888
#     888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
#     888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
#     888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
#     888     888  888 888      X88      888    888 888 Y8b.          888      X88
#     888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
#
#                                                       888                 888
#                                                       888                 888
#                                                       888                 888
#    .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
#   d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
#   888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
#   Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
#    "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
#        888
#   Y8b d88P
#    "Y88P"
#
################################################################################
'''
