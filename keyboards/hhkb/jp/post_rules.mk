ifeq ($(strip $(HHKB_RN42_ENABLE)), yes)

OPT_DEFS += -DHHKB_RN42_ENABLE

# Support for the RN42 Bluetooth module. This is the BT module in Hasu's BT
# HHKB Alt controller.
RN42_DIR = keyboards/hhkb/rn42

SRC +=  serial_uart.c \
	suart.S \
	rn42.c \
	rn42_task.c \
	battery.c \
	main.c

VPATH += $(RN42_DIR)

endif
