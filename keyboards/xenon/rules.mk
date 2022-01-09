# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = yes       # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
# TODO Test this
NKRO_ENABLE = no           # USB Nkey Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality on B7 by default
SPLIT_KEYBOARD = yes       # Split common
OLED_ENABLE = yes          # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
