WIRELESS_ENABLE ?= yes
WIRELESS_DIR = $(TOP_DIR)/keyboards/linker/wireless

ifeq ($(strip $(WIRELESS_ENABLE)), yes)
    OPT_DEFS += -DWIRELESS_ENABLE -DNO_USB_STARTUP_CHECK

    OPT_DEFS += -include $(WIRELESS_DIR)/md_raw.h

    UART_DRIVER_REQUIRED ?= yes
    WIRELESS_LPWR_STOP_ENABLE ?= yes

    VPATH += $(WIRELESS_DIR)

    SRC += \
        $(WIRELESS_DIR)/wireless.c \
        $(WIRELESS_DIR)/transport.c \
        $(WIRELESS_DIR)/lowpower.c \
        $(WIRELESS_DIR)/md_raw.c \
        $(WIRELESS_DIR)/smsg.c \
        $(WIRELESS_DIR)/module.c

    ifeq ($(strip $(WIRELESS_LPWR_STOP_ENABLE)), yes)
        OPT_DEFS += -DWIRELESS_LPWR_STOP_ENABLE
        SRC += $(WIRELESS_DIR)/lpwr_wb32.c
    endif
endif
