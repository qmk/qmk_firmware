EXTRAFLAGS += -flto			# Used to make code smaller
# Build options
BACKLIGHT_ENABLE = yes 		# Switch LEDs
MOUSEKEY_ENABLE = no 		# Emulates mouse key using keypresses
RGBLIGHT_ENABLE = no 		# LED strips
TAP_DANCE_ENABLE = no 		# Use multi-tap features
AUDIO_ENABLE = no  			# Audio stuff
EXTRAKEY_ENABLE = yes 		# Media keys

COMMAND_ENABLE = no			# Some bootmagic thing i dont use
BOOTMAGIC_ENABLE = no 		# Access to EEPROM settings, not needed
CONSOLE_ENABLE = no			# Allows console output with a command
SLEEP_LED_ENABLE = no  		# Breathes LED's when computer is asleep. Untested.
NKRO_ENABLE = no 			# Default is 6KRO which is plenty
MIDI_ENABLE = no 			# Untested feature
FAUXCLICKY_ENABLE = no 		# Emulates clicks using speaker
KEY_LOCK_ENABLE = no 		# Allows locking any key. Not used
API_SYSEX_ENABLE = no 		# Allows OS to send signals.
KEY_LOCK_ENABLE = no 		# Allows locking any key. Not used

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
