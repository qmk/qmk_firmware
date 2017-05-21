
#ifdef SUBPROJECT_teensy2pp
	SCULPT_UPLOAD_COMMAND = teensy_loader_cli -w -mmcu=$(MCU) $(TARGET).hex
#endif

#ifdef SUBPROJECT_astar
	OPT_DEFS += -DCATERINA_BOOTLOADER
	SCULPT_UPLOAD_COMMAND = while [ ! -r $(USB) ]; do sleep 1; done ; \
			 avrdude -p $(MCU) -c avr109 -U flash:w:$(TARGET).hex -P $(USB)

#endif


# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

#
BOOTMAGIC_ENABLE ?= no      # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE ?= no       # Mouse keys(+4700)
EXTRAKEY_ENABLE ?= yes       # Audio control and System control(+450)
CONSOLE_ENABLE ?= yes        # Console for debug(+400)
COMMAND_ENABLE ?= yes        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE ?= no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE ?= no            # USB Nkey Rollover
BACKLIGHT_ENABLE ?= no       # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE ?= no            # MIDI controls
UNICODE_ENABLE ?= no         # Unicode
BLUETOOTH_ENABLE ?= no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE ?= no           # Audio output on port C6


USB ?= /dev/cu.usbmodem1421
 

upload: build
	$(SCULPT_UPLOAD_COMMAND)
