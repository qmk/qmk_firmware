# MCU name
MCU = atmega32a

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
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
WS2812_DRIVER = i2c

LAYOUTS = tkl_f13_ansi tkl_f13_ansi_tsangan tkl_f13_iso tkl_f13_iso_tsangan
