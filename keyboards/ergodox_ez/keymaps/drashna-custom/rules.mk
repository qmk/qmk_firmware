TAP_DANCE_ENABLE  = yes
<<<<<<< HEAD
SLEEP_LED_ENABLE  = no  # Breathing sleep LED during USB suspend
COMMAND_ENABLE    = yes  # Commands for debug and configuration
RGBLIGHT_ENABLE   = yes
MIDI_ENABLE       = no
CONSOLE_ENABLE    = no
LEADER_KEYS       = no

EXTRAFLAGS        = -flto
=======
SLEEP_LED_ENABLE  = yes  # Breathing sleep LED during USB suspend
COMMAND_ENABLE    = no  # Commands for debug and configuration
RGBLIGHT_ENABLE   = yes
MIDI_ENABLE       = no
CONSOLE_ENABLE    = yes
>>>>>>> Updated RGB Underglow info

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
