# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BACKLIGHT_DRIVER = custom

# TODO: This needs to be refactored -- keyboards should not be referencing files from other manufacturers
VPATH += keyboards/lfkeyboards
SRC = TWIlib.c issi.c lighting.c
