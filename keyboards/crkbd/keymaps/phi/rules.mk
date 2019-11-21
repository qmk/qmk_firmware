TAP_DANCE_ENABLE = yes
RGBLIGHT_ENABLE = yes

CUSTOM_MOUSEKEY = yes
ENHANCED_SHIFT = yes

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

SRC += ./keymaps/phi/glcdfont.c
