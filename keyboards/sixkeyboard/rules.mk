# MCU name
MCU = atmega16u2

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no		# Mouse keys
EXTRAKEY_ENABLE = no		# Audio control and System control
CONSOLE_ENABLE = no		# Console for debug
COMMAND_ENABLE = no		# Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no	# Enable keyboard backlight functionality
AUDIO_ENABLE = no
CUSTOM_MATRIX = yes

SRC += matrix.c
LAYOUTS = ortho_2x3
