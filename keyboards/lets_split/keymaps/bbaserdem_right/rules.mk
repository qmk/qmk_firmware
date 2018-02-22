# Build options

BACKLIGHT_ENABLE = no		# Switch LEDs
MOUSEKEY_ENABLE = no		# Emulates mouse key using keypresses
RGBLIGHT_ENABLE = no 		# LED strips
TAP_DANCE_ENABLE = no 		# Use multi-tap features
AUDIO_ENABLE = no 			# Audio stuff
BLUETOOTH_ENABLE = no 		# No bluetooth
COMMAND_ENABLE = no			# Some bootmagic thing
BOOTMAGIC_ENABLE = no 		# Access to EEPROM settings, not needed
CONSOLE_ENABLE = no			# Allows console output with a command
SLEEP_LED_ENABLE = no  		# Breathes LED's when computer is asleep. Untested.
NKRO_ENABLE = no 			# Default is 6KRO which is plenty
MIDI_ENABLE = no 			# Untested feature
FAUXCLICKY_ENABLE = no 		# Emulates clicks using speaker
KEY_LOCK_ENABLE = no 		# Allows locking any key. Not used
API_SYSEX_ENABLE = no 		# Allows OS to send signals.
KEY_LOCK_ENABLE = no 		# Allows locking any key. Not used
UNICODE_ENABLE = no			# Used for unicode character emulation
EXTRAKEY_ENABLE = no		# OS signals like volume control

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
