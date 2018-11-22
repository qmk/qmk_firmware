RGBLIGHT_ENABLE = yes
KEY_LOCK_ENABLE = yes

EXTRAFLAGS      += -flto
UNICODE_ENABLE  = no
MOUSEKEY_ENABLE = no

### Debugging ###
CONSOLE_ENABLE  = no # yes
COMMAND_ENABLE  = no

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
