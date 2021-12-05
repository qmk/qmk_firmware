# MCU name
MCU = at90usb1286

# Bootloader selection
BOOTLOADER = halfkay

# Build Options
#   change to no to disable the options.
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE  = yes # Mouse keys
EXTRAKEY_ENABLE  = yes # Audio control and System control
CONSOLE_ENABLE   = yes # Console for debug
COMMAND_ENABLE   = yes # Commands for debug and configuration
NKRO_ENABLE      = no  # USB Nkey Rollover - not yet supported in LUFA
UNICODE_ENABLE   = yes # Enable support for arrow keys icon on the second layer.
NKRO_ENABLE      = yes
BACKLIGHT_ENABLE = yes
