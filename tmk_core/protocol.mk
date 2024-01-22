SRC +=	\
	$(PROTOCOL_DIR)/host.c \
	$(PROTOCOL_DIR)/report.c \
	$(PROTOCOL_DIR)/usb_device_state.c \
	$(PROTOCOL_DIR)/usb_util.c \

SHARED_EP_ENABLE = no
MOUSE_SHARED_EP ?= yes
ifeq ($(strip $(KEYBOARD_SHARED_EP)), yes)
    OPT_DEFS += -DKEYBOARD_SHARED_EP
    SHARED_EP_ENABLE = yes
    # With the current usb_descriptor.c code,
    # you can't share kbd without sharing mouse;
    # that would be a very unexpected use case anyway
    MOUSE_SHARED_EP = yes
endif

ifeq ($(strip $(MOUSE_ENABLE)), yes)
    OPT_DEFS += -DMOUSE_ENABLE
    ifeq ($(strip $(MOUSE_SHARED_EP)), yes)
        OPT_DEFS += -DMOUSE_SHARED_EP
        SHARED_EP_ENABLE = yes
    endif
endif

ifeq ($(strip $(EXTRAKEY_ENABLE)), yes)
    OPT_DEFS += -DEXTRAKEY_ENABLE
    SHARED_EP_ENABLE = yes
endif

ifeq ($(strip $(PROGRAMMABLE_BUTTON_ENABLE)), yes)
    OPT_DEFS += -DPROGRAMMABLE_BUTTON_ENABLE
    SHARED_EP_ENABLE = yes
endif

ifeq ($(strip $(RAW_ENABLE)), yes)
    OPT_DEFS += -DRAW_ENABLE
endif

ifeq ($(strip $(CONSOLE_ENABLE)), yes)
    OPT_DEFS += -DCONSOLE_ENABLE
else
    # TODO: decouple this so other print backends can exist
    OPT_DEFS += -DNO_PRINT
    OPT_DEFS += -DNO_DEBUG
endif

ifeq ($(strip $(NKRO_ENABLE)), yes)
    ifeq ($(strip $(BLUETOOTH_ENABLE)), yes)
        $(info NKRO is not currently supported with Bluetooth, and has been disabled.)
    else
        OPT_DEFS += -DNKRO_ENABLE
        SHARED_EP_ENABLE = yes
    endif
endif

ifeq ($(strip $(RING_BUFFERED_6KRO_REPORT_ENABLE)), yes)
    OPT_DEFS += -DRING_BUFFERED_6KRO_REPORT_ENABLE
endif

ifeq ($(strip $(NO_SUSPEND_POWER_DOWN)), yes)
    OPT_DEFS += -DNO_SUSPEND_POWER_DOWN
endif

ifeq ($(strip $(NO_USB_STARTUP_CHECK)), yes)
    OPT_DEFS += -DNO_USB_STARTUP_CHECK
endif

ifeq ($(strip $(JOYSTICK_SHARED_EP)), yes)
    OPT_DEFS += -DJOYSTICK_SHARED_EP
    SHARED_EP_ENABLE = yes
endif

ifeq ($(strip $(JOYSTICK_ENABLE)), yes)
    OPT_DEFS += -DJOYSTICK_ENABLE
    ifeq ($(strip $(SHARED_EP_ENABLE)), yes)
        OPT_DEFS += -DJOYSTICK_SHARED_EP
        SHARED_EP_ENABLE = yes
    endif
endif

ifeq ($(strip $(DIGITIZER_SHARED_EP)), yes)
    OPT_DEFS += -DDIGITIZER_SHARED_EP
    SHARED_EP_ENABLE = yes
endif

ifeq ($(strip $(DIGITIZER_ENABLE)), yes)
    OPT_DEFS += -DDIGITIZER_ENABLE
    ifeq ($(strip $(SHARED_EP_ENABLE)), yes)
        OPT_DEFS += -DDIGITIZER_SHARED_EP
        SHARED_EP_ENABLE = yes
    endif
endif

ifeq ($(strip $(SHARED_EP_ENABLE)), yes)
    OPT_DEFS += -DSHARED_EP_ENABLE
endif

ifeq ($(strip $(USB_HID_ENABLE)), yes)
    include $(TMK_DIR)/protocol/usb_hid/usb_hid.mk
endif

# Search Path
VPATH += $(TMK_DIR)/protocol
