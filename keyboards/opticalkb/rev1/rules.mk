# https://docs.qmk.fm/#/squeezing_avr?id=rulesmk-settings
#

# MCU name
MCU = STM32F401

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
KEYBOARD_SHARED_EP = yes

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
DYNAMIC_MACRO_ENABLE = yes  # Dynamic macros

LED_MATRIX_ENABLE = no

# turn this off after debugging
# CONSOLE_ENABLE = yes

# https://github.com/qmk/qmk_firmware/blob/master/docs/custom_matrix.md
CUSTOM_MATRIX = lite
SRC += matrix.c
