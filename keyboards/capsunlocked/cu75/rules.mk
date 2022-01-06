# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BACKLIGHT_DRIVER = custom

SRC = ../lfkeyboards/TWIlib.c ../lfkeyboards/issi.c ../lfkeyboards/lighting.c
