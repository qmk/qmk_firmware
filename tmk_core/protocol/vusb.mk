VUSB_DIR = protocol/vusb

# Path to the V-USB library
VUSB_PATH = $(LIB_PATH)/vusb

SRC += $(VUSB_DIR)/main.c \
	$(VUSB_DIR)/vusb.c \
	$(VUSB_PATH)/usbdrv/usbdrv.c \
	$(VUSB_PATH)/usbdrv/usbdrvasm.S \
	$(VUSB_PATH)/usbdrv/oddebug.c

# Search Path
VPATH += $(TMK_PATH)/$(VUSB_DIR)
VPATH += $(VUSB_PATH)

OPT_DEFS += -DPROTOCOL_VUSB
