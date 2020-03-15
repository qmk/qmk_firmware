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
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = custom
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = yes
COMMAND_ENABLE = no
NKRO_ENABLE = yes
AUDIO_ENABLE = yes
RGBLIGHT_ENABLE = yes
MIDI_ENABLE = no
UNICODE_ENABLE = no
BLUETOOTH_ENABLE = no

EXTRAFLAGS += -flto
LAYOUTS = 66_ansi
