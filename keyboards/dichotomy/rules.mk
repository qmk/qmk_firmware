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
#BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000)
#MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
POINTING_DEVICE_ENABLE = yes # Generic Pointer, not as big as mouse keys hopefully.
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = yes	# Console for debug(+400)
COMMAND_ENABLE = yes   # Commands for debug and configuration
CUSTOM_MATRIX = yes    # Remote matrix from the wireless bridge
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
# SLEEP_LED_ENABLE = yes  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# USB Nkey Rollover - not yet supported in LUFA
# BACKLIGHT_ENABLE = yes  # Enable keyboard backlight functionality
# MIDI_ENABLE = YES 		# MIDI controls
UNICODE_ENABLE = YES 		# Unicode
# BLUETOOTH_ENABLE = yes # Enable Bluetooth with the Adafruit EZ-Key HID

USB = /dev/ttyACM0

OPT_DEFS += -DDICHOTOMY_PROMICRO
DICHOTOMY_UPLOAD_COMMAND = while [ ! -r $(USB) ]; do sleep 1; done; \
                         avrdude -p $(MCU) -c avr109 -U flash:w:$(TARGET).hex -P $(USB)

# # project specific files
SRC = matrix.c

#upload: build
#	$(DICHOTOMY_UPLOAD_COMMAND)
