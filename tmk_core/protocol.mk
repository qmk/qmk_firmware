PROTOCOL_DIR = protocol

TMK_COMMON_SRC +=	\
	$(PROTOCOL_DIR)/host.c \
	$(PROTOCOL_DIR)/report.c \
	$(PROTOCOL_DIR)/usb_device_state.c \
	$(PROTOCOL_DIR)/usb_util.c \

ifeq ($(strip $(USB_HID_ENABLE)), yes)
    include $(TMK_DIR)/protocol/usb_hid.mk
endif

# Search Path
VPATH += $(TMK_DIR)/protocol
