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

# Supported processor types
CHIBIOS_PROCESSORS = 'cortex-m0', 'cortex-m0plus', 'cortex-m3', 'cortex-m4', 'MKL26Z64', 'MK20DX128', 'MK20DX256', 'MK64FX512', 'MK66FX1M0', 'RP2040', 'STM32F042', 'STM32F072', 'STM32F103', 'STM32F303', 'STM32F401', 'STM32F405', 'STM32F407', 'STM32F411', 'STM32F446', 'STM32G431', 'STM32G474', 'STM32L412', 'STM32L422', 'STM32L432', 'STM32L433', 'STM32L442', 'STM32L443', 'GD32VF103', 'WB32F3G71', 'WB32FQ95'
LUFA_PROCESSORS = 'at90usb162', 'atmega16u2', 'atmega32u2', 'atmega16u4', 'atmega32u4', 'at90usb646', 'at90usb647', 'at90usb1286', 'at90usb1287', None
VUSB_PROCESSORS = 'atmega32a', 'atmega328p', 'atmega328', 'attiny85'

# Bootloaders of the supported processors
MCU2BOOTLOADER = {
    "RP2040": "rp2040",
    "MKL26Z64": "halfkay",
    "MK20DX128": "halfkay",
    "MK20DX256": "halfkay",
    "MK66FX1M0": "halfkay",
    "STM32F042": "stm32-dfu",
    "STM32F072": "stm32-dfu",
    "STM32F103": "stm32duino",
    "STM32F303": "stm32-dfu",
    "STM32F401": "stm32-dfu",
    "STM32F405": "stm32-dfu",
    "STM32F407": "stm32-dfu",
    "STM32F411": "stm32-dfu",
    "STM32F446": "stm32-dfu",
    "STM32G431": "stm32-dfu",
    "STM32G474": "stm32-dfu",
    "STM32L412": "stm32-dfu",
    "STM32L422": "stm32-dfu",
    "STM32L432": "stm32-dfu",
    "STM32L433": "stm32-dfu",
    "STM32L442": "stm32-dfu",
    "STM32L443": "stm32-dfu",
    "GD32VF103": "gd32v-dfu",
    "WB32F3G71": "wb32-dfu",
    "WB32FQ95": "wb32-dfu",
    "atmega16u2": "atmel-dfu",
    "atmega32u2": "atmel-dfu",
    "atmega16u4": "atmel-dfu",
    "atmega32u4": "atmel-dfu",
    "at90usb162": "atmel-dfu",
    "at90usb646": "atmel-dfu",
    "at90usb647": "atmel-dfu",
    "at90usb1286": "atmel-dfu",
    "at90usb1287": "atmel-dfu",
    "atmega32a": "bootloadhid",
    "atmega328p": "usbasploader",
    "atmega328": "usbasploader",
}

# Map of legacy keycodes that can be automatically updated
LEGACY_KEYCODES = {  # Comment here is to force multiline formatting
    'RESET': 'QK_BOOT'
}

# Map VID:PID values to bootloaders
BOOTLOADER_VIDS_PIDS = {
    'atmel-dfu': {
        ("03eb", "2fef"),  # ATmega16U2
        ("03eb", "2ff0"),  # ATmega32U2
        ("03eb", "2ff3"),  # ATmega16U4
        ("03eb", "2ff4"),  # ATmega32U4
        ("03eb", "2ff9"),  # AT90USB64
        ("03eb", "2ffa"),  # AT90USB162
        ("03eb", "2ffb")  # AT90USB128
    },
    'kiibohd': {("1c11", "b007")},
    'stm32-dfu': {
        ("1eaf", "0003"),  # STM32duino
        ("0483", "df11")  # STM32 DFU
    },
    'apm32-dfu': {("314b", "0106")},
    'gd32v-dfu': {("28e9", "0189")},
    'bootloadhid': {("16c0", "05df")},
    'usbasploader': {("16c0", "05dc")},
    'usbtinyisp': {("1782", "0c9f")},
    'md-boot': {("03eb", "6124")},
    'caterina': {
        # pid.codes shared PID
        ("1209", "2302"),  # Keyboardio Atreus 2 Bootloader
        # Spark Fun Electronics
        ("1b4f", "9203"),  # Pro Micro 3V3/8MHz
        ("1b4f", "9205"),  # Pro Micro 5V/16MHz
        ("1b4f", "9207"),  # LilyPad 3V3/8MHz (and some Pro Micro clones)
        # Pololu Electronics
        ("1ffb", "0101"),  # A-Star 32U4
        # Arduino SA
        ("2341", "0036"),  # Leonardo
        ("2341", "0037"),  # Micro
        # Adafruit Industries LLC
        ("239a", "000c"),  # Feather 32U4
        ("239a", "000d"),  # ItsyBitsy 32U4 3V3/8MHz
        ("239a", "000e"),  # ItsyBitsy 32U4 5V/16MHz
        # dog hunter AG
        ("2a03", "0036"),  # Leonardo
        ("2a03", "0037")  # Micro
    },
    'hid-bootloader': {
        ("03eb", "2067"),  # QMK HID
        ("16c0", "0478")  # PJRC halfkay
    }
}

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
