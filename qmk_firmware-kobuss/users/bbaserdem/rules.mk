SRC += bbaserdem.c
EXTRAFLAGS += -flto			# Used to make code smaller

# ENABLE
UNICODE_ENABLE = yes	# Used for unicode character emulation
EXTRAKEY_ENABLE = yes 	# OS signals like volume control

# DISABLE
ifndef BLUETOOTH_ENABLE 
	BLUETOOTH_ENABLE = no 	# No bluetooth
endif
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

# Disabling this makes it compile, i dont know why
# VARIABLE_TRACE = no 		# Allows debugging variables
