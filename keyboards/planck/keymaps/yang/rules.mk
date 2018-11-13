# Build Options
#   change to "no" to disable the options, or define them in the Makefile in 
#   the appropriate keymap folder that will get included automatically
#
RGBLIGHT_ENABLE = yes        # Enable WS2812 RGB underlight. 
AUDIO_ENABLE = no

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif