# MCU name
MCU = STM32F401

# Bootloader selection
BOOTLOADER = tinyuf2

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
KEYBOARD_SHARED_EP = yes
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
#BACKLIGHT_DRIVER = software
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
WS2812_DRIVER = bitbang
AUDIO_ENABLE = no           # Audio output

LAYOUTS = ortho_5x12