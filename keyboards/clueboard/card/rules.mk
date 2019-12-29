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
BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes      # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes      # Audio control and System control(+450)
CONSOLE_ENABLE = yes       # Console for debug(+400)
COMMAND_ENABLE = yes       # Commands for debug and configuration
NKRO_ENABLE = no           # USB Nkey Rollover
RGBLIGHT_ENABLE = yes      # Enable keyboard underlight functionality (+4870)
BACKLIGHT_ENABLE = yes     # Enable keyboard backlight functionality by default
MIDI_ENABLE = no           # MIDI controls
UNICODE_ENABLE = no        # Unicode
BLUETOOTH_ENABLE = no      # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = yes         # Audio output on port C6

LINK_TIME_OPTIMIZATION_ENABLE = yes
