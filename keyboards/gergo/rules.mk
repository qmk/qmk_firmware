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

CUSTOM_MATRIX 		= yes
EXTRAKEY_ENABLE		= yes
CONSOLE_ENABLE  	= yes
COMMAND_ENABLE		= yes
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite

DEBOUNCE_TYPE = sym_eager_pr
SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c
