# MCU name
MCU = atmega32u2

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
# Comment out to disable the options.
BOOTMAGIC_ENABLE = lite
MOUSEKEY_ENABLE = yes			# Mouse keys
EXTRAKEY_ENABLE = yes			# Audio control and System control
CONSOLE_ENABLE = no			# Console for debug
COMMAND_ENABLE = no			# Commands for debug and configuration
KEYBOARD_LOCK_ENABLE = no		# Allow locking of keyboard via magic key
SLEEP_LED_ENABLE = no			# Breathing sleep LED during USB suspend
NKRO_ENABLE = yes			# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no			# Enable keyboard backlight functionality
BLUETOOTH_ENABLE = no			# Enable Bluetooth
