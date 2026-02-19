# RN42 Bluetooth Support

ifeq ($(strip $(HHKB_RN42_ENABLE)), yes)
    OPT_DEFS += -DHHKB_RN42_ENABLE
    RN42_DIR = keyboards/hhkb/rn42
    SRC += $(RN42_DIR)/serial_uart.c \
           $(RN42_DIR)/suart.S \
           $(RN42_DIR)/rn42.c \
           $(RN42_DIR)/rn42_task.c \
           $(RN42_DIR)/battery.c
    VPATH += $(RN42_DIR)
    EXTRAINCDIRS += $(RN42_DIR)
endif
