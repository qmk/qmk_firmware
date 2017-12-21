CONSOLE_ENABLE    = no
COMMAND_ENABLE    = no  # Commands for debug and configuration
TAP_DANCE_ENABLE  = yes
RGBLIGHT_ENABLE   = yes
MOUSEKEY_ENABLE   = no
NKRO_ENABLE       = yes

EXTRAFLAGS        = -flto

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
