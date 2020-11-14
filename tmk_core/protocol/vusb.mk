VUSB_DIR = protocol/vusb

OPT_DEFS += -DPROTOCOL_VUSB

SRC +=	$(VUSB_DIR)/main.c \
	$(VUSB_DIR)/vusb.c \
	$(VUSB_DIR)/usbdrv/usbdrv.c \
	$(VUSB_DIR)/usbdrv/usbdrvasm.S \
	$(VUSB_DIR)/usbdrv/oddebug.c


ifneq ($(strip $(CONSOLE_ENABLE)), yes)
ifndef NO_UART
SRC +=	$(COMMON_DIR)/sendchar_uart.c \
	$(COMMON_DIR)/uart.c
endif
endif

# Search Path
VPATH += $(TMK_PATH)/$(VUSB_DIR)
VPATH += $(TMK_PATH)/$(VUSB_DIR)/usbdrv
