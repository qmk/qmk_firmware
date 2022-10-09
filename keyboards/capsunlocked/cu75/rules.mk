# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BACKLIGHT_DRIVER = custom

# TODO: These boards need to be converted to RGB Matrix
VPATH += keyboards/lfkeyboards
SRC = TWIlib.c issi.c lighting.c
