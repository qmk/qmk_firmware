# MCU selection
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

# build options
BOOTMAGIC_ENABLE = no   # Virtual DIP switch configuration
MOUSEKEY_ENABLE  = no   # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes  # Audio control and System control(+450)
CONSOLE_ENABLE   = no   # Console for debug
COMMAND_ENABLE   = no   # Commands for debug and configuration
BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
UNICODE_ENABLE   = no   # Unicode

LAYOUTS = ortho_5x4 ortho_6x4 numpad_5x4 numpad_6x4
