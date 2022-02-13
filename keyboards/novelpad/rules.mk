# MCU name
MCU = atmega32u2

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = yes  # In-switch LEDs
AUDIO_ENABLE = no      # There is no available timer or pin for audio on the NovelPad
RGBLIGHT_ENABLE = yes  # RGB LEDs for underglow, installed and enabled by default for the NovelPad

LAYOUTS = ortho_5x4
