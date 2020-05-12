# Build Options
#   change to "no" to disable the options, or define them in the Makefile in 
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover 
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
ifeq ($(strip $(KEYBOARD)), handwired/ms_sculpt_mobile/8x18_arm)
	RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight. 
endif
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

#enable RAW in keymap config, since it can hang machines
RAW_ENABLE = no
# virtual serial port
VIRTSER_ENABLE = yes
