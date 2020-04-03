"""Information that should be available to the python library.
"""
from pathlib import Path

# The root of the qmk_firmware tree.
QMK_FIRMWARE = Path.cwd()

# This is the number of directories under `qmk_firmware/keyboards` that will be traversed. This is currently a limitation of our make system.
MAX_KEYBOARD_SUBFOLDERS = 5

# These mirror C constants with the same name
DYNAMIC_KEYMAP_EEPROM_MAX_ADDR = 1023
EECONFIG_SIZE = 34
DYNAMIC_KEYMAP_EEPROM_ADDR = 4
DYNAMIC_MACRO_SIZE = 128
# Space for dynamic keymaps
DYNAMIC_KEYMAP_EEPROM_SIZE = DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - EECONFIG_SIZE - DYNAMIC_KEYMAP_EEPROM_ADDR - DYNAMIC_MACRO_SIZE
# The number of layers VIA uses by default
VIA_DEFAULT_NUMBER_OF_LAYERS = 4
