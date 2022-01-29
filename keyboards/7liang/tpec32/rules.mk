# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE 		= yes		# Enable Bootmagic Lite
CONSOLE_ENABLE 			= no        # Console for debug
COMMAND_ENABLE 			= no        # Commands for debug and configuration
NKRO_ENABLE 			= yes       # Enable N-Key Rollover
BACKLIGHT_ENABLE 		= no        # Enable keyboard backlight functionality
AUDIO_ENABLE 			= no        # Audio output
SLEEP_LED_ENABLE		= no

SRC += tp_encoder.c

DEFAULT_FOLDER = 7liang/tpec32/v1
