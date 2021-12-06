# MCU name
MCU = STM32F103

MCU_LDSCRIPT = m12og_v1

BOARD = m12og_v1

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # HAS TO BE ON! Otherwise the custom matrix doesn't work
AUDIO_ENABLE = no           # Audio output

CUSTOM_MATRIX = lite
SRC += matrix.c
