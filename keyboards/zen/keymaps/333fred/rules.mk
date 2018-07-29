RGBLIGHT_ENABLE = yes
BACKLIGHT_ENABLE = yes
NKRO_ENABLE = yes
KEY_LOCK_ENABLE = yes
TAP_DANCE_ENABLE = yes
CONSOLE_ENABLE = no

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
