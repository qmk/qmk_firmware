# MCU name
MCU = atmega32u4

F_CPU = 16000000

ARCH = AVR8

F_USB = $(F_CPU)

BOOTLOADER = atmel-dfu

# Interrupt driven control endpoint task
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE	= lite	# Virtual DIP switch configuration(+1000)
# MOUSEKEY_ENABLE	= yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE		= yes	# Audio control and System control(+450)
# CONSOLE_ENABLE	= yes	# Console for debug(+400)
# COMMAND_ENABLE	= yes  	# Commands for debug and configuration
# SLEEP_LED_ENABLE 	= yes  	# Breathing sleep LED during USB suspend
# NKRO_ENABLE 		= yes	# USB Nkey Rollover - not yet supported in LUFA
# BACKLIGHT_ENABLE = yes
USB_HID_ENABLE = yes

CUSTOM_MATRIX = yes
SRC += custom_matrix.cpp\
	main.c
