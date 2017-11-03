CONSOLE_ENABLE    = no
TAP_DANCE_ENABLE  = yes
RGBLIGHT_ENABLE   = yes
MOUSEKEY_ENABLE   = no
NKRO_ENABLE       = yes

EXTRAFLAGS        = -flto

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
