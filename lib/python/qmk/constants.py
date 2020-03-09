"""Information that should be available to the python library.
"""
from pathlib import Path

# The root of the qmk_firmware tree.
QMK_FIRMWARE = Path.cwd()

# This is the number of directories under `qmk_firmware/keyboards` that will be traversed. This is currently a limitation of our make system.
MAX_KEYBOARD_SUBFOLDERS = 5

# The number of layers VIA uses by default
VIA_NUMBER_OF_LAYERS = 4
