TAP_DANCE_ENABLE  = yes
SLEEP_LED_ENABLE  = no  # Breathing sleep LED during USB suspend
COMMAND_ENABLE    = no  # Commands for debug and configuration
RGBLIGHT_ENABLE   = yes
CONSOLE_ENABLE    = no

EXTRAFLAGS        = -flto

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
