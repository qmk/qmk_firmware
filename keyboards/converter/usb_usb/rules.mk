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
#   comment out to disable the options.
#
#BOOTMAGIC_ENABLE = yes  # Virtual DIP switch configuration(+1000)
#MOUSEKEY_ENABLE  = yes  # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes  # Audio control and System control(+450)
#CONSOLE_ENABLE   = yes  # Console for debug(+400)
#COMMAND_ENABLE   = yes  # Commands for debug and configuration
#SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
#NKRO_ENABLE      = yes  # USB Nkey Rollover - not yet supported in LUFA
#BACKLIGHT_ENABLE = yes
USB_HID_ENABLE   = yes
CUSTOM_MATRIX    = yes

SRC = custom_matrix.cpp

DEFAULT_FOLDER = converter/usb_usb/hasu
