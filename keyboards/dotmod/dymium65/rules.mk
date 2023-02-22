# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
MOUSEKEY_ENABLE = yes       # Mouse keys

ENCODER_MAP_ENABLE = yes    # Enable ENCODER MAP
ENCODER_ENABLE = yes	    # Enable ENCODER
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support

BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
