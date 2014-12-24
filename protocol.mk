PROTOCOL_DIR = protocol


ifdef PS2_MOUSE_ENABLE
    SRC += $(PROTOCOL_DIR)/ps2_mouse.c
    OPT_DEFS += -DPS2_MOUSE_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
endif

ifdef PS2_USE_BUSYWAIT
    SRC += protocol/ps2_busywait.c
    SRC += protocol/ps2_io_avr.c
    OPT_DEFS += -DPS2_USE_BUSYWAIT
endif

ifdef PS2_USE_INT
    SRC += protocol/ps2_interrupt.c
    SRC += protocol/ps2_io_avr.c
    OPT_DEFS += -DPS2_USE_INT
endif

ifdef PS2_USE_USART
    SRC += protocol/ps2_usart.c
    SRC += protocol/ps2_io_avr.c
    OPT_DEFS += -DPS2_USE_USART
endif


ifdef SERIAL_MOUSE_MICROSOFT_ENABLE
    SRC += $(PROTOCOL_DIR)/serial_mouse_microsoft.c
    OPT_DEFS += -DSERIAL_MOUSE_ENABLE -DSERIAL_MOUSE_MICROSOFT \
                -DMOUSE_ENABLE
endif

ifdef SERIAL_MOUSE_MOUSESYSTEMS_ENABLE
    SRC += $(PROTOCOL_DIR)/serial_mouse_mousesystems.c
    OPT_DEFS += -DSERIAL_MOUSE_ENABLE -DSERIAL_MOUSE_MOUSESYSTEMS \
                -DMOUSE_ENABLE
endif

ifdef SERIAL_MOUSE_USE_SOFT
    SRC += $(PROTOCOL_DIR)/serial_soft.c
endif

ifdef SERIAL_MOUSE_USE_UART
    SRC += $(PROTOCOL_DIR)/serial_uart.c
endif

# Search Path
VPATH += $(TOP_DIR)/protocol
