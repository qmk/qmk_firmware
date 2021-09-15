# MCU name
MCU = atmega32a

# Bootloader selection
BOOTLOADER = bootloadhid

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
MOUSEKEY_ENABLE  = no       # Mouse keys
EXTRAKEY_ENABLE  = yes      # Audio control and System control
CONSOLE_ENABLE   = no       # Console for debug
COMMAND_ENABLE   = yes      # Commands for debug and configuration
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE  = no       # Enable keyboard RGB underglow
