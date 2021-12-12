# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = no	# Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
AUDIO_ENABLE = no

RGBLIGHT_ENABLE = no

LAYOUTS = 65_ansi
