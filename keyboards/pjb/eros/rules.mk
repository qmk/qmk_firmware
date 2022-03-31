# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = bootloadHID

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
BACKLIGHT_ENABLE = no     # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Enable audio output
WS2812_DRIVER = i2c
VIA_ENABLE = yes
