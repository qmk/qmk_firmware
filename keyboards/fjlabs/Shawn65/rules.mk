# Microcontroller Options
MCU = atmega32u4

# Processor frequency.
#     Overwrite the default processor frequency of
#	  16MHz since these boards use an 8MHz  crystal in the
#	  interest of reducing overall power consumption. No change
#	  in overall performance is expected from this choice.
F_CPU = 8000000 

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
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = lite		# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes		# Mouse keys
EXTRAKEY_ENABLE = yes		# Audio control and System control
#CONSOLE_ENABLE = yes		# Console for debug
COMMAND_ENABLE = yes		# Commands for debug and configuration
KEYBOARD_LOCK_ENABLE = yes	# Allow locking of keyboard via magic key
NKRO_ENABLE = yes			# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes		# Enable RGB Underglow support

LAYOUTS = 65_ansi
