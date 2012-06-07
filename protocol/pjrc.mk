OPT_DEFS += -DHOST_PJRC

SRC +=	pjrc.c \
	usb_keyboard.c \
	usb_debug.c \
	usb.c \
	bootloader_teensy.c


# Search Path
VPATH += $(TOP_DIR)/protocol/pjrc


# Option modules
ifdef $(or MOUSEKEY_ENABLE, PS2_MOUSE_ENABLE)
    SRC += usb_mouse.c
endif

ifdef EXTRAKEY_ENABLE
    SRC += usb_extra.c
endif
