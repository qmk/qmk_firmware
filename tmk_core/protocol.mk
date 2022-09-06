PROTOCOL_DIR = protocol

ifeq ($(strip $(PS2_MOUSE_ENABLE)), yes)
    SRC += $(PROTOCOL_DIR)/ps2_mouse.c
    OPT_DEFS += -DPS2_MOUSE_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
endif

ifeq ($(strip $(PS2_USE_BUSYWAIT)), yes)
    SRC += protocol/ps2_busywait.c
    SRC += protocol/ps2_io_avr.c
    OPT_DEFS += -DPS2_USE_BUSYWAIT
endif

ifeq ($(strip $(PS2_USE_INT)), yes)
    SRC += protocol/ps2_interrupt.c
    SRC += protocol/ps2_io_avr.c
    OPT_DEFS += -DPS2_USE_INT
endif

ifeq ($(strip $(PS2_USE_USART)), yes)
    SRC += protocol/ps2_usart.c
    SRC += protocol/ps2_io_avr.c
    OPT_DEFS += -DPS2_USE_USART
endif


ifeq ($(strip $(SERIAL_MOUSE_MICROSOFT_ENABLE)), yes)
    SRC += $(PROTOCOL_DIR)/serial_mouse_microsoft.c
    OPT_DEFS += -DSERIAL_MOUSE_ENABLE -DSERIAL_MOUSE_MICROSOFT \
                -DMOUSE_ENABLE
endif

ifeq ($(strip $(SERIAL_MOUSE_MOUSESYSTEMS_ENABLE)), yes)
    SRC += $(PROTOCOL_DIR)/serial_mouse_mousesystems.c
    OPT_DEFS += -DSERIAL_MOUSE_ENABLE -DSERIAL_MOUSE_MOUSESYSTEMS \
                -DMOUSE_ENABLE
endif

ifeq ($(strip $(SERIAL_MOUSE_USE_SOFT)), yes)
    SRC += $(PROTOCOL_DIR)/serial_soft.c
endif

ifeq ($(strip $(SERIAL_MOUSE_USE_UART)), yes)
    SRC += $(PROTOCOL_DIR)/serial_uart.c
endif

ifeq ($(strip $(ADB_MOUSE_ENABLE)), yes)
    OPT_DEFS += -DADB_MOUSE_ENABLE -DMOUSE_ENABLE
endif

ifeq ($(strip $(XT_ENABLE)), yes)
    SRC += $(PROTOCOL_DIR)/xt_interrupt.c
    OPT_DEFS += -DXT_ENABLE
endif

ifeq ($(strip $(USB_HID_ENABLE)), yes)
    include $(TMK_DIR)/protocol/usb_hid.mk
endif

# Search Path
VPATH += $(TMK_DIR)/protocol
