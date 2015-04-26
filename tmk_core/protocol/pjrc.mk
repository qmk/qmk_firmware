PJRC_DIR = protocol/pjrc

SRC +=	$(PJRC_DIR)/main.c \
	$(PJRC_DIR)/pjrc.c \
	$(PJRC_DIR)/usb_keyboard.c \
	$(PJRC_DIR)/usb_debug.c \
	$(PJRC_DIR)/usb.c

# Option modules
ifdef MOUSEKEY_ENABLE
    SRC += $(PJRC_DIR)/usb_mouse.c
endif

ifdef ADB_MOUSE_ENABLE
    SRC += $(PJRC_DIR)/usb_mouse.c
endif

ifdef PS2_MOUSE_ENABLE
    SRC += $(PJRC_DIR)/usb_mouse.c
endif

ifdef EXTRAKEY_ENABLE
    SRC += $(PJRC_DIR)/usb_extra.c
endif

# Search Path
VPATH += $(TMK_DIR)/$(PJRC_DIR)

# This indicates using LUFA stack
OPT_DEFS += -DPROTOCOL_PJRC
