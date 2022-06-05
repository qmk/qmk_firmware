MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE  = yes   # Enable Bootmagic Lite
CONSOLE_ENABLE 	  = no    # Console for debug
COMMAND_ENABLE 	  = no    # Commands for debug and configuration
RGB_MATRIX_ENABLE = yes   # RGB Matrix
UNICODEMAP_ENABLE = yes   # Enables UNICODE MAP. Map is maintained in keymap.c, and requires WinCompose on Windows to work
LTO_ENABLE		  = yes   # Reduce firmware binary size
