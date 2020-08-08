CUSTOM_MATRIX = lite

# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no
COMMAND_ENABLE = yes
NKRO_ENABLE = yes
CUSTOM_MATRIX = lite

# Project specific files
SRC += matrix.c

# experimentally determined to be sufficient :)
DEBOUNCE=1
