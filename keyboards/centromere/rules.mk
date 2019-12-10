# MCU name
MCU = atmega32u4

# Processor frequency
F_CPU = 8000000

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina
F_CPU = 8000000

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = yes	# Console for debug(+400)
COMMAND_ENABLE = yes   # Commands for debug and configuration
CUSTOM_MATRIX = yes    # Remote matrix from the wireless bridge
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
# SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# USB Nkey Rollover - not yet supported in LUFA
# BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
# MIDI_ENABLE = yes 		# MIDI controls
UNICODE_ENABLE = yes 		# Unicode
# BLUETOOTH_ENABLE = yes # Enable Bluetooth with the Adafruit EZ-Key HID

USB = /dev/ttyACM0

# upload: build
# 	$(CENTROMERE_UPLOAD_COMMAND)

OPT_DEFS += -DCENTROMERE_PROMICRO

# # project specific files
SRC = matrix.c
