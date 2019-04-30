# MCU name
MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)

OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT -DONLYQWERTY -DDEBUG_MATRIX
SRC += sten.c
EXTRAFLAGS += -flto


BOOTLOADER = atmel-dfu
MOUSEKEY_ENABLE 	= yes		# Mouse keys(+4700)
EXTRAKEY_ENABLE 	= yes       # Audio control and System control(+450)
CONSOLE_ENABLE 		= yes       # Console for debug(+400)
COMMAND_ENABLE 		= no		# Commands for debug and configuration
NKRO_ENABLE 		= yes       # USB Nkey Rollover
STENO_ENABLE		= yes 		# Needed for chording

