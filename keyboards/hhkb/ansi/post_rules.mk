ifeq ($(strip $(HHKB_RN42_ENABLE)), yes)

OPT_DEFS += -DHHKB_RN42_ENABLE

# Support for the RN42 Bluetooth module. This is the BT module in Hasu's BT
# HHKB Alt controller.
RN42_DIR = ../rn42

SRC +=  serial_uart.c \
	../rn42/suart.S \
	../rn42/rn42.c \
	../rn42/rn42_task.c \
	../rn42/battery.c \
	../rn42/main.c

VPATH += $(RN42_DIR)

endif
