# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = no        # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
BACKLIGHT_DRIVER = custom
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = yes

CUSTOM_MATRIX = yes
SRC += matrix.c \

LAYOUTS = 75_ansi
