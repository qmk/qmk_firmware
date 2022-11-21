# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = qmk-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_DRIVER = WS2812

SPLIT_KEYBOARD = yes
LAYOUTS = ortho_4x12 ortho_5x12

DEFAULT_FOLDER = rgbkb/zygomorph/rev1

# Disable unsupported hardware
AUDIO_SUPPORTED = no
BACKLIGHT_SUPPORTED = no
