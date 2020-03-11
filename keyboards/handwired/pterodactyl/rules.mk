# MCU name
MCU = atmega32u4
F_CPU = 8000000

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
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE        = no  # Virtual DIP switch configuration(+1000)
MIDI_ENABLE             = no  # MIDI support (+2400 to 4200)
POINTING_DEVICE_ENABLE  = no
MOUSEKEY_ENABLE         = no  # Mouse keys(+4700)
EXTRAKEY_ENABLE         = yes # Audio control and System control(+450)
CONSOLE_ENABLE          = no  # Console for debug(+8000)
COMMAND_ENABLE          = no  # Commands for debug and configuration
CUSTOM_MATRIX           = yes # Custom matrix file for the pterodactyl
NKRO_ENABLE             = yes # USB Nkey Rollover
UNICODE_ENABLE          = yes # Unicode
SWAP_HANDS_ENABLE       = yes # Allow swapping hands of keyboard
SLEEP_LED_ENABLE        = no
API_SYSEX_ENABLE        = no
RGBLIGHT_ENABLE         = no
BLUETOOTH_ENABLE        = yes # Enable Bluetooth with the Adafruit EZ-Key HID
BLUETOOTH               = AdafruitBLE

# project specific files
SRC = twimaster.c \
	  matrix.c
