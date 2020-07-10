# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
OLED_DRIVER_ENABLE = yes    # Enables the use of OLED displays
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
SPLIT_KEYBOARD = yes       # Split common

LAYOUTS = split_3x5_3
