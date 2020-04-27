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
CONSOLE_ENABLE = no
SPLIT_KEYBOARD = yes
DIPS_ENABLE = no
PHYSICAL_LEDS_ENABLE = yes
CAPS_LOCK_LED_ENABLE = yes
NUM_LOCK_LED_ENABLE = yes
SCROLL_LOCK_LED_ENABLE = yes
BACKLIGHT_ENABLE = yes
RGBLIGHT_ENABLE = yes
