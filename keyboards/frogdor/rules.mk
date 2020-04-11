MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
CONSOLE_ENABLE = no        	# Console for debug
COMMAND_ENABLE = no      	# Commands for debug and configuration
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes           # USB Nkey Rollover
ENCODER_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes