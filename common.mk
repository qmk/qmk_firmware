SRC +=	host.c \
	keyboard.c \
	command.c \
	layer.c \
	timer.c \
	print.c \
	bootloader.c \
	util.c


# Option modules
ifdef MOUSEKEY_ENABLE
    SRC += mousekey.c
    OPT_DEFS += -DMOUSEKEY_ENABLE
endif

ifdef PS2_MOUSE_ENABLE
    SRC += ps2.c \
	   ps2_mouse.c
    OPT_DEFS += -DPS2_MOUSE_ENABLE
endif

ifdef EXTRAKEY_ENABLE
    OPT_DEFS += -DEXTRAKEY_ENABLE
endif

ifdef NKRO_ENABLE
    OPT_DEFS += -DNKRO_ENABLE
endif

ifdef $(or MOUSEKEY_ENABLE, PS2_MOUSE_ENABLE)
    OPT_DEFS += -DMOUSE_ENABLE
endif

# Search Path
VPATH += $(TOP_DIR)/common
