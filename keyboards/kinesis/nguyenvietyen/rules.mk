CUSTOM_MATRIX = lite

# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Project specific files
SRC += matrix.c

# experimentally determined to be sufficient :)
DEBOUNCE=1
