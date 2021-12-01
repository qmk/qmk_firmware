# MCU name
MCU = atmega32u4

# Processor frequency
F_CPU = 8000000

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE  = no   # Mouse keys
CONSOLE_ENABLE   = yes  # Console for debug
COMMAND_ENABLE   = no   # Commands for debug and configuration
NKRO_ENABLE      = no   # USB Nkey Rollover - not yet supported in LUFA
EXTRAKEY_ENABLE  = yes
USB_HID_ENABLE   = yes
BACKLIGHT_ENABLE = no
CUSTOM_MATRIX    = yes

SRC = matrix.c m0110.c
