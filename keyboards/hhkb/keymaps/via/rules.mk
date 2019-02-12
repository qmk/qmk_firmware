

# project specific files
SRC += keyboards/wilba_tech/wt_main.c


RAW_ENABLE = yes
DYNAMIC_KEYMAP_ENABLE = yes

# HHKB_RN42_ENABLE = yes  # Enable support for hasu's BT alt controller -- code borrowed from tmk source tree.

# Either uncomment the HHKB_RN42_ENABLE line above, or run make enabling the
# feature. Be sure to clean any existing build before trying to enable rn42
# support. For example:
#
# make hhkb-keymap-clean
# make hhkb-keymap-dfu HHKB_RN42_ENABLE=yes

ifeq ($(strip $(HHKB_RN42_ENABLE)), yes)

OPT_DEFS += -DHHKB_RN42_ENABLE

# Support for the RN42 Bluetooth module. This is the BT module in Hasu's BT
# HHKB Alt controller.
RN42_DIR = rn42

SRC +=  serial_uart.c \
	rn42/suart.S \
	rn42/rn42.c \
	rn42/rn42_task.c \
	rn42/battery.c \
	rn42/main.c

VPATH += $(RN42_DIR)

endif


# debug-on: EXTRAFLAGS += -DDEBUG -DDEBUG_ACTION
# debug-on: all

# debug-off: EXTRAFLAGS += -DNO_DEBUG -DNO_PRINT
# debug-off: OPT_DEFS := $(filter-out -DCONSOLE_ENABLE,$(OPT_DEFS))
# debug-off: all
