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

HELIX_TOP_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# QMK Standard Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
#   See TOP/docs/config_options.md for more information.
#
BOOTMAGIC_ENABLE = no   # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no    # Mouse keys(+4700)
EXTRAKEY_ENABLE = no    # Audio control and System control(+450)
CONSOLE_ENABLE = no     # Console for debug(+400)
COMMAND_ENABLE = no     # Commands for debug and configuration
NKRO_ENABLE = no        # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no   # Enable keyboard backlight functionality
MIDI_ENABLE = no        # MIDI controls
AUDIO_ENABLE = no       # Audio output on port C6
UNICODE_ENABLE = no     # Unicode
BLUETOOTH_ENABLE = no   # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend

DEFAULT_FOLDER = helix/rev2
