# MCU
MCU = RP2040

# Board
BOARD = GENERIC_RP_RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Split Keyboard Stuff
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor

# Enable Bootmagic Lite
BOOTMAGIC_ENABLE = yes

# Default Folder
DEFAULT_FOLDER = junco/rev1

SRC += junco_sync.c
