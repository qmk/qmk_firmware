# MCU name
MCU = atmega32a

# Bootloader selection
BOOTLOADER = bootloadhid

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no   # Mouse keys
EXTRAKEY_ENABLE = yes  # Audio control and System control
CONSOLE_ENABLE = no    # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = yes # Enable keyboard backlight functionality
AUDIO_ENABLE = no      # Audio output
RGBLIGHT_ENABLE = yes  # Enable WS2812 RGB underlight. 
WS2812_DRIVER = i2c

LAYOUTS = planck_mit
LAYOUTS_HAS_RGB = no
