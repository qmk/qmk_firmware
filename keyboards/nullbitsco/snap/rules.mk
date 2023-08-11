# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
AUDIO_ENABLE = no          # Audio output
SPLIT_KEYBOARD = yes       # Split common
LTO_ENABLE = yes           # Use Link Time Optimization
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
SPACE_CADET_ENABLE = no    # Enables the use of Space Cadet
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
CUSTOM_MATRIX = lite       # Split custom matrix

# Project specific files
SRC +=  common/bitc_led.c \
        common/remote_kb.c \
        matrix.c \
        uart.c
