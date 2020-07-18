"""Information that should be available to the python library.
"""
from pathlib import Path

# The root of the qmk_firmware tree.
QMK_FIRMWARE = Path.cwd()

# This is the number of directories under `qmk_firmware/keyboards` that will be traversed. This is currently a limitation of our make system.
MAX_KEYBOARD_SUBFOLDERS = 5

# Supported processor types
ARM_PROCESSORS = 'cortex-m0', 'cortex-m0plus', 'cortex-m3', 'cortex-m4', 'MKL26Z64', 'MK20DX128', 'MK20DX256', 'STM32F042', 'STM32F072', 'STM32F103', 'STM32F303'
AVR_PROCESSORS = 'at90usb1286', 'at90usb646', 'atmega16u2', 'atmega328p', 'atmega32a', 'atmega32u2', 'atmega32u4', None
ALL_PROCESSORS = ARM_PROCESSORS + AVR_PROCESSORS
VUSB_PROCESSORS = 'atmega328p', 'atmega32a', 'atmega328', 'attiny85'
