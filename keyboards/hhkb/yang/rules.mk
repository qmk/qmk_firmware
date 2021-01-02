# MCU name
MCU = atmega32u4

# MCU frequency
F_CPU = 8000000

# Bootloader selection
BOOTLOADER = lufa-ms

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover

LAYOUTS = 60_hhkb

# Disable bluetooth until the UART code is merged
# BLUETOOTH = AdafruitBLE_UART

# Custom matrix file for the HHKB
CUSTOM_MATRIX = yes
SRC += matrix.c

# Disable debounce
DEBOUNCE_TYPE = custom
