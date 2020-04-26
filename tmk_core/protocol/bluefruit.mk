BLUEFRUIT_DIR = protocol/bluefruit

SRC +=	$(BLUEFRUIT_DIR)/main.c \
	$(BLUEFRUIT_DIR)/bluefruit.c \
	serial_uart.c

# Search Path
VPATH += $(TMK_DIR)/$(BLUEFRUIT_DIR)
#VPATH += $(TMK_DIR)/$(BLUEFRUIT_DIR)/usb_debug_only

OPT_DEFS += -DPROTOCOL_BLUEFRUIT
