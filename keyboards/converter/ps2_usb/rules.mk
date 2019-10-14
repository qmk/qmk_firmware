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
BOOTLOADER = halfkay

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = lite   # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = no  # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes  # Audio control and System control(+450)
CONSOLE_ENABLE   = yes  # Console for debug(+400)
COMMAND_ENABLE   = yes  # Commands for debug and configuration
NKRO_ENABLE      = yes  # USB Nkey Rollover
CUSTOM_MATRIX    = yes
#PS2_USE_INT    = yes #use for soarer's converter
PS2_USE_USART = yes #use if using Hasu converter.

SRC = matrix.c
# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax
