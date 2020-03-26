ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

USER_NAME = anderson
OPT_DEFS += -DLIGHTMODE_ENABLE
SRC += taphold.c smoothled.c dmc12.c seq.c lightmode.c

