SRC += tap_dance.c
RGBLIGHT_ENABLE = yes
TAP_DANCE_ENABLE = yes

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
