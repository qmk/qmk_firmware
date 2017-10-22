TAP_DANCE_ENABLE  = yes
SLEEP_LED_ENABLE  = yes  # Breathing sleep LED during USB suspend
COMMAND_ENABLE    = no  # Commands for debug and configuration
RGBLIGHT_ENABLE   = yes
MIDI_ENABLE       = no
CONSOLE_ENABLE    = no
LEADER_KEYS       = no
ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
