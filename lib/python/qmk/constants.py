"""Information that should be available to the python library.
"""
from pathlib import Path

# The root of the qmk_firmware tree.
QMK_FIRMWARE = Path.cwd()

# This is the number of directories under `qmk_firmware/keyboards` that will be traversed. This is currently a limitation of our make system.
MAX_KEYBOARD_SUBFOLDERS = 5

# Supported processor types
CHIBIOS_PROCESSORS = 'cortex-m0', 'cortex-m0plus', 'cortex-m3', 'cortex-m4', 'MKL26Z64', 'MK20DX128', 'MK20DX256', 'STM32F042', 'STM32F072', 'STM32F103', 'STM32F303', 'STM32F401', 'STM32F411'
LUFA_PROCESSORS = 'atmega16u2', 'atmega32u2', 'atmega16u4', 'atmega32u4', 'at90usb646', 'at90usb647', 'at90usb1286', 'at90usb1287', None
VUSB_PROCESSORS = 'atmega32a', 'atmega328p', 'atmega328', 'attiny85'

# Common format strings
DATE_FORMAT = '%Y-%m-%d'
DATETIME_FORMAT = '%Y-%m-%d %H:%M:%S %Z'
TIME_FORMAT = '%H:%M:%S'

# Used when generating matrix locations
COL_LETTERS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijilmnopqrstuvwxyz'
ROW_LETTERS = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnop'
