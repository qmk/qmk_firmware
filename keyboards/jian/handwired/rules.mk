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
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
SPLIT_KEYBOARD = no
DIPS_ENABLE = no
PHYSICAL_LEDS_ENABLE = no
CAPS_LOCK_LED_ENABLE = no
NUM_LOCK_LED_ENABLE = no
SCROLL_LOCK_LED_ENABLE = no
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = no
