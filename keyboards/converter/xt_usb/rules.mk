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
BOOTMAGIC_ENABLE = no   # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = yes  # Mouse keys(+4700)
EXTRAKEY_ENABLE  = yes  # Audio control and System control(+450)
CONSOLE_ENABLE   = yes  # Console for debug(+400)
COMMAND_ENABLE   = yes  # Commands for debug and configuration
NKRO_ENABLE      = yes  # USB Nkey Rollover
XT_ENABLE        = yes
CUSTOM_MATRIX    = yes

SRC = matrix.c led.c

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax
