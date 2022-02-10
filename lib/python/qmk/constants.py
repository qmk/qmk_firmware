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

# Supported processor types
CHIBIOS_PROCESSORS = 'cortex-m0', 'cortex-m0plus', 'cortex-m3', 'cortex-m4', 'MKL26Z64', 'MK20DX128', 'MK20DX256', 'MK66FX1M0', 'STM32F042', 'STM32F072', 'STM32F103', 'STM32F303', 'STM32F401', 'STM32F405', 'STM32F407', 'STM32F411', 'STM32F446', 'STM32G431', 'STM32G474', 'STM32L412', 'STM32L422', 'STM32L432', 'STM32L433', 'STM32L442', 'STM32L443', 'GD32VF103', 'WB32F3G71'
LUFA_PROCESSORS = 'at90usb162', 'atmega16u2', 'atmega32u2', 'atmega16u4', 'atmega32u4', 'at90usb646', 'at90usb647', 'at90usb1286', 'at90usb1287', None
VUSB_PROCESSORS = 'atmega32a', 'atmega328p', 'atmega328', 'attiny85'

# Bootloaders of the supported processors
MCU2BOOTLOADER = {
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
