# MCU name
MCU = atmega32u4
BOOTLOADER = atmel-dfu

CUSTOM_MATRIX 		= yes
EXTRAKEY_ENABLE		= yes
CONSOLE_ENABLE  	= yes
COMMAND_ENABLE		= yes
BOOTMAGIC_ENABLE 	= lite
STENO_ENABLE			= yes
NKRO_ENABLE				= yes
DEBOUNCE_TYPE  		= eager_pr

SRC 						+= matrix.c sten.c
QUANTUM_LIB_SRC += i2c_master.c
OPT_DEFS 				+= -DONLYQWERTY -DDEBUG_MATRIX
EXTRAFLAGS 			+= -flto
