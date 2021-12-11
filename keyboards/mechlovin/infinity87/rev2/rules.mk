# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu


# Build Options
#   change yes to no to disable
#
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = yes
RGBLIGHT_ENABLE = yes
CUSTOM_MATRIX = lite

SRC += matrix.c
