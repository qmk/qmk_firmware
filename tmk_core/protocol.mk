ifeq ($(strip $(PS2_MOUSE_ENABLE)), yes)
    PS2_ENABLE := yes
    SRC += ps2_mouse.c
    OPT_DEFS += -DPS2_MOUSE_ENABLE
    OPT_DEFS += -DMOUSE_ENABLE
endif

ifeq ($(strip $(PS2_USE_BUSYWAIT)), yes)
    PS2_ENABLE := yes
    SRC += ps2_busywait.c
    SRC += ps2_io_avr.c
    OPT_DEFS += -DPS2_USE_BUSYWAIT
endif

ifeq ($(strip $(PS2_USE_INT)), yes)
    PS2_ENABLE := yes
    SRC += ps2_interrupt.c
    SRC += ps2_io.c
    OPT_DEFS += -DPS2_USE_INT
endif

ifeq ($(strip $(PS2_USE_USART)), yes)
    PS2_ENABLE := yes
    SRC += ps2_usart.c
    SRC += ps2_io.c
    OPT_DEFS += -DPS2_USE_USART
endif

ifeq ($(strip $(PS2_ENABLE)), yes)
    COMMON_VPATH += $(DRIVER_PATH)/ps2
    COMMON_VPATH += $(PLATFORM_PATH)/$(PLATFORM_KEY)/$(DRIVER_DIR)/ps2
    OPT_DEFS += -DPS2_ENABLE
endif


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
