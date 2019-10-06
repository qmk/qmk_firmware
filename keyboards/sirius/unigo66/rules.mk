# MCU name
MCU = atmega32u4

F_CPU = 16000000

ARCH = AVR8

F_USB = $

BOOTLOADER = atmel-dfu

# Interrupt driven control endpoint task
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE	= lite	# Virtual DIP switch configuration
# MOUSEKEY_ENABLE	= yes	# Mouse keys
EXTRAKEY_ENABLE		= yes	# Audio control and System control
# CONSOLE_ENABLE	= yes	# Console for debug
# COMMAND_ENABLE	= yes  	# Commands for debug and configuration
# SLEEP_LED_ENABLE 	= yes  	# Breathing sleep LED during USB suspend
# NKRO_ENABLE 		= yes	# USB Nkey Rollover - not yet supported in LUFA
# BACKLIGHT_ENABLE = yes
USB_HID_ENABLE = yes

CUSTOM_MATRIX = yes
SRC += custom_matrix.cpp\
	main.c
