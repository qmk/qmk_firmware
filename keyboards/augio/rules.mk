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

# Build Options
#   comment out to disable the options.
#
# EXTRAFLAGS+=-flto
LTO_ENABLE = yes
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = lite  # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no # Mouse keys
EXTRAKEY_ENABLE = yes # Audio control and System control
CONSOLE_ENABLE = no  # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes     # USB Nkey Rollover
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no
SERIAL_LINK_ENABLE = no

