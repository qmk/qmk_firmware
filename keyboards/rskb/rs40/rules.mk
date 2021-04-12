# MCU name
MCU = atmega32u4


BOOTLOADER = atmel-dfu
# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
AUDIO_ENABLE = yes           # Audio output on port C6
VIA_ENABLE = yes