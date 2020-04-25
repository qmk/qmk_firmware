# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

CUSTOM_MATRIX 			= yes
MOUSEKEY_ENABLE			= yes
STENO_ENABLE 				= yes
EXTRAKEY_ENABLE     = yes
CONSOLE_ENABLE      = yes
COMMAND_ENABLE      = no
NKRO_ENABLE					= yes
BOOTMAGIC_ENABLE = lite

EXTRAFLAGS 		+= -flto
SRC 					+= matrix.c i2c_master.c g/engine.c
VPATH         +=  keyboards/gboards/ 
