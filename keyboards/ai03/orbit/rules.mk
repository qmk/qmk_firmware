# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
USE_I2C = no                # I2C for split communication
CUSTOM_MATRIX = yes			# For providing custom matrix.c (in this case, override regular matrix.c with split matrix.c)
# SPLIT_KEYBOARD = yes		# Split keyboard flag disabled as manual edits had to be done to the split common files

SRC += split_util.c \
	   split_flags.c \
	   serial.c \
	   transport.c \
	   matrix.c
