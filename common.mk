COMMON_DIR = common
SRC +=	$(COMMON_DIR)/host.c \
	$(COMMON_DIR)/keyboard.c \
	$(COMMON_DIR)/command.c \
	$(COMMON_DIR)/layer.c \
	$(COMMON_DIR)/timer.c \
	$(COMMON_DIR)/print.c \
	$(COMMON_DIR)/bootloader.c \
	$(COMMON_DIR)/util.c


# Option modules
ifdef MOUSEKEY_ENABLE
    SRC += $(COMMON_DIR)/mousekey.c
    OPT_DEFS += -DMOUSEKEY_ENABLE
endif

ifdef EXTRAKEY_ENABLE
    OPT_DEFS += -DEXTRAKEY_ENABLE
endif

ifdef CONSOLE_ENABLE
    OPT_DEFS += -DCONSOLE_ENABLE
endif

ifdef NKRO_ENABLE
    OPT_DEFS += -DNKRO_ENABLE
endif

ifdef PS2_MOUSE_ENABLE
    SRC += $(COMMON_DIR)/ps2.c \
           $(COMMON_DIR)/ps2_mouse.c
    OPT_DEFS += -DPS2_MOUSE_ENABLE
endif

ifdef $(or MOUSEKEY_ENABLE, PS2_MOUSE_ENABLE)
    OPT_DEFS += -DMOUSE_ENABLE
endif

# Search Path
VPATH += $(TOP_DIR)/common
