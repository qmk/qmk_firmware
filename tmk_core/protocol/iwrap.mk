IWRAP_DIR = protocol/iwrap

OPT_DEFS += -DPROTOCOL_IWRAP

SRC +=	$(IWRAP_DIR)/main.c \
	$(IWRAP_DIR)/iwrap.c \
	$(IWRAP_DIR)/suart.S \
	$(COMMON_DIR)/sendchar_uart.c \
	$(COMMON_DIR)/uart.c

# Search Path
VPATH += $(TMK_DIR)/protocol/iwrap


# TODO: compatible with LUFA and PJRC
# V-USB
#
VUSB_DIR = protocol/vusb

# Path to the V-USB library
VUSB_PATH = $(LIB_PATH)/vusb

SRC += $(VUSB_DIR)/vusb.c \
	$(VUSB_PATH)/usbdrv/usbdrv.c \
	$(VUSB_PATH)/usbdrv/usbdrvasm.S \
	$(VUSB_PATH)/usbdrv/oddebug.c

# Search Path
VPATH += $(TMK_PATH)/$(VUSB_DIR)
VPATH += $(VUSB_PATH)

OPT_DEFS += -DPROTOCOL_VUSB
