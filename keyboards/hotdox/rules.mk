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
CUSTOM_MATRIX           = yes # Custom matrix file for the ErgoDone
UNICODE_ENABLE          = yes # Unicode
BOOTMAGIC_ENABLE        = yes # Virtual DIP switch configuration
MOUSEKEY_ENABLE         = yes  # Mouse keys
EXTRAKEY_ENABLE         = yes # Audio control and System control
CONSOLE_ENABLE          = yes # Console for debug
COMMAND_ENABLE          = no  # Commands for debug and configuration
SLEEP_LED_ENABLE        = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE             = yes # USB Nkey Rollover - not yet supported in LUFA
USB_6KRO_ENABLE         = no  # USB 6key Rollover
BACKLIGHT_ENABLE        = yes # Enable keyboard backlight functionality
SWAP_HANDS_ENABLE       = no  # Disable Onehand
RGBLIGHT_ENABLE         = no
MIDI_ENABLE             = no

# project specific files
SRC =  matrix.c     \
	   i2c_master.c \
       left.c

LAYOUTS = ergodox
