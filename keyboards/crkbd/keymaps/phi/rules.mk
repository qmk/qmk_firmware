MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
RGBLIGHT_ENABLE = yes

ENHANCED_SHIFT = yes

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

SRC += ./keymaps/phi/glcdfont.c
