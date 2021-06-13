# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
COMMAND_ENABLE = yes
NKRO_ENABLE = yes
SLEEP_LED_ENABLE = yes
CUSTOM_MATRIX = lite
SRC += matrix.c

# experimentally determined to be sufficient :)
DEBOUNCE=1
