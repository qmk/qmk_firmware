IWRAP_DIR = protocol/iwrap

OPT_DEFS += -DPROTOCOL_IWRAP

SRC +=	$(IWRAP_DIR)/main.c \
	$(IWRAP_DIR)/iwrap.c \
	$(IWRAP_DIR)/suart.S \
	$(COMMON_DIR)/sendchar_uart.c \
	$(COMMON_DIR)/uart.c

# Search Path
VPATH += $(TOP_DIR)/protocol/iwrap


# TODO: compatible with LUFA and PJRC
# V-USB
#
VUSB_DIR = protocol/vusb
OPT_DEFS += -DPROTOCOL_VUSB
SRC +=	$(VUSB_DIR)/vusb.c \
	$(VUSB_DIR)/usbdrv/usbdrv.c \
	$(VUSB_DIR)/usbdrv/usbdrvasm.S \
	$(VUSB_DIR)/usbdrv/oddebug.c
VPATH += $(TOP_DIR)/protocol/vusb:$(TOP_DIR)/protocol/vusb/usbdrv


