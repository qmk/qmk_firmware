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
SRC += matrix.c i2c_master.c sten.c
