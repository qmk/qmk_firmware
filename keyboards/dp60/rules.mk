# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Use RGB underglow light
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3731 # Use RGB matrix

LAYOUTS = 60_ansi 60_hhkb 60_iso 60_ansi_split_bs_rshift

CUSTOM_MATRIX = yes
SRC += matrix.c
