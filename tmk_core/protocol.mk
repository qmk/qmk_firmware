PROTOCOL_DIR = protocol

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

ifeq ($(strip $(USB_HID_ENABLE)), yes)
    include $(TMK_DIR)/protocol/usb_hid.mk
endif

# Search Path
VPATH += $(TMK_DIR)/protocol
