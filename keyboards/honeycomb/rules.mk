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
#BOOTMAGIC_ENABLE = full	# Virtual DIP switch configuration
#MOUSEKEY_ENABLE = yes	# Mouse keys
POINTING_DEVICE_ENABLE = yes # Generic Pointer, not as big as mouse keys hopefully.
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = yes   # Commands for debug and configuration
CUSTOM_MATRIX = yes    # Remote matrix from the wireless bridge
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
# SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# USB Nkey Rollover - not yet supported in LUFA
# BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
# MIDI_ENABLE = YES 		# MIDI controls
UNICODE_ENABLE = YES 		# Unicode
# BLUETOOTH_ENABLE = yes # Enable Bluetooth with the Adafruit EZ-Key HID

# # project specific files
SRC += matrix.c serial_uart.c
