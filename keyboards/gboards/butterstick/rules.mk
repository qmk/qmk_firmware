# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
MOUSEKEY_ENABLE 	= yes		# Mouse keys
EXTRAKEY_ENABLE 	= yes       # Audio control and System control
CONSOLE_ENABLE 		= yes       # Console for debug
COMMAND_ENABLE 		= no		# Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
LTO_ENABLE = yes
