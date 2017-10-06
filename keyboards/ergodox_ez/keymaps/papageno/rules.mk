BOOTMAGIC_ENABLE=no
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
FORCE_NKRO ?= yes
DEBUG_ENABLE = no
CONSOLE_ENABLE = no
TAP_DANCE_ENABLE = no
PAPAGENO_ENABLE = yes
KEYLOGGER_ENABLE ?= no
UCIS_ENABLE = no
MOUSEKEY_ENABLE = no
AUTOLOG_ENABLE ?= no
#EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
EXTRAKEY_ENABLE = no       # Audio control and System control(+450)
NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls

# ifeq (${KEYBOARD},planck)
# AUDIO_ENABLE = yes           # Audio output on port C6
# else
AUDIO_ENABLE = no           # Audio output on port C6
# endif
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
