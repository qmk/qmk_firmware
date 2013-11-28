BLUEFRUIT_DIR = protocol/bluefruit
PJRC_DIR = protocol/pjrc

SRC +=	$(BLUEFRUIT_DIR)/main.c \
	$(BLUEFRUIT_DIR)/bluefruit.c \
	serial_uart.c \
	$(PJRC_DIR)/pjrc.c \
	$(PJRC_DIR)/usb_keyboard.c \
	$(PJRC_DIR)/usb_debug.c \
	$(PJRC_DIR)/usb.c

# Option modules
ifdef $(or MOUSEKEY_ENABLE, PS2_MOUSE_ENABLE)
    SRC += $(PJRC_DIR)/usb_mouse.c
endif

ifdef EXTRAKEY_ENABLE
    SRC += $(PJRC_DIR)/usb_extra.c
endif

# Search Path
VPATH += $(TOP_DIR)/$(BLUEFRUIT_DIR)
#VPATH += $(TOP_DIR)/$(BLUEFRUIT_DIR)/usb_debug_only
VPATH += $(TOP_DIR)/$(PJRC_DIR)

OPT_DEFS += -DPROTOCOL_BLUEFRUIT
OPT_DEFS += -DPROTOCOL_PJRC
