# MCU name
MCU = atmega32u2

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes      	# Mouse keys
EXTRAKEY_ENABLE = yes      	# Audio control and System control
CONSOLE_ENABLE = no        	# Console for debug
COMMAND_ENABLE = no        	# Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
RGB_MATRIX_ENABLE = no     # Enable per-key coordinate based RGB effects. Do not enable with RGBlight
RGB_MATRIX_DRIVER = WS2812
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
UNICODE_ENABLE = yes        # Unicode
AUDIO_ENABLE = no           # Audio output
