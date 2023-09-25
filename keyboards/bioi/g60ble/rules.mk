# Processor frequency
F_CPU = 8000000

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes     # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes      # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = yes       # Commands for debug and configuration
BACKLIGHT_ENABLE = yes     # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes
LTO_ENABLE = yes

BLUETOOTH_ENABLE = yes

QUANTUM_LIB_SRC += uart.c
SRC += bluetooth_custom.c
