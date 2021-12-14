# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no       # Mouse keys
ENCODER_ENABLE = yes       # Rotary encoders
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = yes       # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
COMBO_ENABLE = yes         # Key combo feature
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
AUDIO_ENABLE = no          # Audio output
RGBLIGHT_ENABLE = yes      # Enable WS2812 RGB underlight.
