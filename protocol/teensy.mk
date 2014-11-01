TEENSY_PROTOCOL_DIR = protocol/teensy

SRC +=	$(TEENSY_PROTOCOL_DIR)/main.c \
		$(TEENSY_PROTOCOL_DIR)/teensy_driver.c 

# Option modules
ifdef MOUSEKEY_ENABLE
#    SRC += $(PJRC_DIR)/usb_mouse.c
endif

ifdef PS2_MOUSE_ENABLE
#    SRC += $(PJRC_DIR)/usb_mouse.c
endif

ifdef EXTRAKEY_ENABLE
#    SRC += $(PJRC_DIR)/usb_extra.c
endif

# Search Path
VPATH += $(TOP_DIR)/$(TEENSY_PROTOCOL_DIR)

# This indicates using LUFA stack
OPT_DEFS += -DPROTOCOL_TEENSY
