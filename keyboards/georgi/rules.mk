# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

CUSTOM_MATRIX 		= yes
MOUSEKEY_ENABLE		= no
STENO_ENABLE 		= yes
EXTRAKEY_ENABLE     = yes
CONSOLE_ENABLE      = yes
COMMAND_ENABLE      = no
NKRO_ENABLE			= yes

EXTRAFLAGS += -flto
SRC += matrix.c sten.c
I2C_MASTER_DRIVER_REQUIRED := yes

