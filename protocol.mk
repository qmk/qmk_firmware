PROTOCOL_DIR = protocol


ifdef PS2_MOUSE_ENABLE
    SRC += $(PROTOCOL_DIR)/ps2_mouse.c
    OPT_DEFS += -DPS2_MOUSE_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
endif

ifdef PS2_USE_BUSYWAIT
    SRC += protocol/ps2_busywait.c
    OPT_DEFS += -DPS2_USE_BUSYWAIT
endif

ifdef PS2_USE_INT
    SRC += protocol/ps2_interrupt.c
    OPT_DEFS += -DPS2_USE_INT
endif

ifdef PS2_USE_USART
    SRC += protocol/ps2_usart.c
    OPT_DEFS += -DPS2_USE_USART
endif


# Search Path
VPATH += $(TOP_DIR)/protocol
