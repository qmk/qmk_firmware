# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

CUSTOM_MATRIX 		= yes
EXTRAKEY_ENABLE		= yes
CONSOLE_ENABLE  	= yes
COMMAND_ENABLE		= yes
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite

DEBOUNCE_TYPE = sym_eager_pr
SRC += matrix.c
I2C_MASTER_DRIVER_REQUIRED := yes
