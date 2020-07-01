# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina


AUDIO_ENABLE = no
BACKLIGHT_ENABLE = no   # Enable keyboard backlight functionality
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
COMMAND_ENABLE = no     # Commands for debug and configuration
CONSOLE_ENABLE= no	# Console for debug
EXTRAKEY_ENABLE = yes	# Audio control and System control
MOUSEKEY_ENABLE = yes	# Mouse keys
NKRO_ENABLE = yes	# USB Nkey Rollover -

RGBLIGHT_ENABLE = no
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
UNICODE_ENABLE = yes
TAP_DANCE_ENABLE = yes
