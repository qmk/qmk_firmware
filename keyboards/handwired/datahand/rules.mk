# MCU name
MCU = at90usb1286

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = halfkay

# Build Options
BOOTMAGIC_ENABLE  = no   # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   = yes  # Mouse keys(+4700)
EXTRAKEY_ENABLE   = yes  # Audio control and System control(+450)
CONSOLE_ENABLE    = yes  # Console for debug(+400)
COMMAND_ENABLE    = yes  # Commands for debug and configuration
NKRO_ENABLE       = yes  # USB Nkey Rollover
BACKLIGHT_ENABLE  = no   # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE       = no   # MIDI controls
UNICODE_ENABLE    = no   # Unicode
BLUETOOTH_ENABLE  = no   # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE      = no   # Audio output (needs a pin configured in config.h, see docs/feature_audio.md)
CUSTOM_MATRIX     = yes  # We definitely have a nonstandard matrix

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

# Project specific files
SRC = matrix.c
