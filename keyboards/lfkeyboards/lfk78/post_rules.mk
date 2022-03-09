# Extra source files for IS3731 lighting
SRC += TWIlib.c issi.c lighting.c

ifeq ($(strip $(ISSI_ENABLE)), yes)
    TMK_COMMON_DEFS += -DISSI_ENABLE
endif

ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
    TMK_COMMON_DEFS += -DWATCHDOG_ENABLE
endif

ifeq ($(strip $(CAPSLOCK_LED)), yes)
    TMK_COMMON_DEFS += -DCAPSLOCK_LED
endif
