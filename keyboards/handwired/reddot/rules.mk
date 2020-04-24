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
ifdef TEENSY2
    BOOTLOADER = halfkay
    OPT_DEFS += -DATREUS_TEENSY2
    ATREUS_UPLOAD_COMMAND = teensy_loader_cli -w -mmcu=$(MCU) $(TARGET).hex
else
    BOOTLOADER = caterina
    OPT_DEFS += -DATREUS_ASTAR
    ATREUS_UPLOAD_COMMAND = while [ ! -r $(USB) ]; do sleep 1; done; \
                            avrdude -p $(MCU) -c avr109 -U flash:w:$(TARGET).hex -P $(USB)
endif

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no        # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE = no            # MIDI controls
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output (needs a pin configured in config.h, see docs/feature_audio.md)

# upload: build
# 	$(ATREUS_UPLOAD_COMMAND)

# for avr upload
USB = /dev/cu.usbmodem1421
