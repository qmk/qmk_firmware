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

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no   # virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE  = yes  # mouse keys(+4700)
EXTRAKEY_ENABLE  = no   # audio control and System control(+450)
CONSOLE_ENABLE   = no   # console for debug(+400)
COMMAND_ENABLE   = no   # commands for debug and configuration
CUSTOM_MATRIX    = yes    # Remote matrix from the wireless bridge
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes		# USB Nkey Rollover
BACKLIGHT_ENABLE = no  # Enable keyboard backlight functionality
MIDI_ENABLE = no 		# MIDI controls
UNICODE_ENABLE = yes 		# Unicode
BLUETOOTH_ENABLE = no # Enable Bluetooth with the Adafruit EZ-Key HID

TAP_DANCE_ENABLE = yes  # enable double tap completion of (),[],{}
# upload: build
# 	$(CENTROMERE_UPLOAD_COMMAND)

OPT_DEFS += -DCENTROMERE_PROMICRO
