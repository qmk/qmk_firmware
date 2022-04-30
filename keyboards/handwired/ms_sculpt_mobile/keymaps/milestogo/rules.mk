# only things overriding defaults
#
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover 
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight. 
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend


ifeq ($(strip $(KEYBOARD)), handwired/ms_sculpt_mobile/8x18_arm)
	RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight. 
endif

#enable RAW in keymap config, since it can hang machines
RAW_ENABLE = no
# virtual serial port
VIRTSER_ENABLE = no

USER_NAME := miles2go

# Keymap specific files
