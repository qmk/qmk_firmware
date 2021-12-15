# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no    # Mouse keys
EXTRAKEY_ENABLE = no    # Audio control and System control
CONSOLE_ENABLE = no     # Console for debug
COMMAND_ENABLE = no     # Commands for debug and configuration
CUSTOM_MATRIX = yes     # Remote matrix from the wireless bridge
NKRO_ENABLE = yes           # Enable N-Key Rollover
# BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality

# project specific files
SRC += matrix.c \
       i2c.c \
       ssd1306.c \
       serial_uart.c
