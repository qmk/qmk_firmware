PROTOCOL_DIR = protocol

ifeq ($(strip $(USB_HID_ENABLE)), yes)
    include $(TMK_DIR)/protocol/usb_hid.mk
endif

# Search Path
VPATH += $(TMK_DIR)/protocol
