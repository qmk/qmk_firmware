# MCU name
MCU = atmega32u4

# Processor frequency
F_CPU = 8000000

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes   # Commands for debug and configuration
CUSTOM_MATRIX = yes    # Remote matrix from the wireless bridge
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
UNICODE_ENABLE = yes 		# Unicode

# # project specific files
SRC += matrix.c serial_uart.c

LAYOUTS = split_3x5_3 split_3x6_3
