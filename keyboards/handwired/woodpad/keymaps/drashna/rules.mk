TAP_DANCE_ENABLE  = yes
COMMAND_ENABLE    = no  # Commands for debug and configuration
RGBLIGHT_ENABLE   = yes
MIDI_ENABLE       = no
CONSOLE_ENABLE    = no
NKRO_ENABLE       = yes
MOUSEKEY_ENABLE   = no

EXTRAFLAGS        = -flto

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
