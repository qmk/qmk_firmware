# MCU name
MCU = atmega32a

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = bootloadHID

# build options
BOOTMAGIC_ENABLE ?= yes # Virtual DIP switch configuration
MOUSEKEY_ENABLE ?= no   # Mouse keys
EXTRAKEY_ENABLE ?= yes  # Audio control and System control
CONSOLE_ENABLE ?= no    # Console for debug
COMMAND_ENABLE ?= no    # Commands for debug and configuration
NKRO_ENABLE ?= no       # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ # nkro-doesnt-work
BACKLIGHT_ENABLE ?= yes # Enable keyboard backlight functionality
MIDI_ENABLE ?= no       # MIDI controls
AUDIO_ENABLE ?= no      # Audio output on port C6
UNICODE_ENABLE ?= no    # Unicode
BLUETOOTH_ENABLE ?= no  # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE ?= yes  # Enable WS2812 RGB underlight. 
WS2812_DRIVER = i2c
TAP_DANCE_ENABLE = no

OPT_DEFS = -DDEBUG_LEVEL=0

LAYOUTS = planck_mit
LAYOUTS_HAS_RGB = no
