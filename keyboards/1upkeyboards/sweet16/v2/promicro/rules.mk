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

## Features
CONSOLE_ENABLE = yes

## On a Pro Micro you have to choose between underglow and the rotary encoder.
RGBLIGHT_ENABLE = no
ENCODER_ENABLE = yes

LINK_TIME_OPTIMIZATION_ENABLE = yes
