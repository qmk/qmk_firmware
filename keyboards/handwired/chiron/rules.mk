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
SPLIT_KEYBOARD = yes

# Build Options
#   change yes to no to disable
#
AUDIO_ENABLE = no
AUTOLOG_ENABLE = no
BACKLIGHT_ENABLE = no
BLUETOOTH_ENABLE = no
BOOTMAGIC_ENABLE = no
COMMAND_ENABLE = no
CONSOLE_ENABLE = no
DEBUG_ENABLE = no
EXTRAKEY_ENABLE = no
FAUXCLICKY_ENABLE = no
HD44780_ENABLE = no
LEADER_ENABLE = no
MIDI_ENABLE = no
MOUSEKEY_ENABLE = yes
NKRO_ENABLE = no
RGBLIGHT_ENABLE = yes
SLEEP_LED_ENABLE = yes
TAP_DANCE_ENABLE = no
UCIS_ENABLE = no
UNICODEMAP_ENABLE = no
UNICODE_ENABLE = no
