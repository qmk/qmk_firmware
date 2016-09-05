SLEEP_LED_ENABLE = no 
COMMAND_ENABLE   = no 
FORCE_NKRO ?= yes
TAP_DANCE_ENABLE = yes
	
ifeq (${FORCE_NKRO},yes)
	OPT_DEFS += -DFORCE_NKRO
endif

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
