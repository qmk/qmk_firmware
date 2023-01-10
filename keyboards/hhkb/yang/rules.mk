# MCU name
MCU = atmega32u4

# MCU frequency
F_CPU = 8000000

# Bootloader selection
BOOTLOADER = lufa-ms

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = no            # USB Nkey Rollover

# Disable bluetooth until the UART code is merged
BLUETOOTH_DRIVER = BluefruitLE

# Custom matrix file for the HHKB
CUSTOM_MATRIX = lite
SRC += matrix.c
