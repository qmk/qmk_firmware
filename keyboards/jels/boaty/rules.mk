# MCU name
MCU = atmega328p

BOOTLOADER = usbasploader

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for deb
NKRO_ENABLE = no            # USB Nkey Rollover - Doesn't work with USBasp
BACKLIGHT_ENABLE = no 	    # Enable keyboard backlight functionality on B7 by default

