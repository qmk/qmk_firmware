RN42_DIR = rn42

SRC +=  serial_uart.c \
	rn42/suart.S \
	rn42/rn42.c \
	rn42/rn42_task.c \
	rn42/battery.c \
	rn42/main.c

OPT_DEFS += -DPROTOCOL_RN42

VPATH += $(RN42_DIR)
