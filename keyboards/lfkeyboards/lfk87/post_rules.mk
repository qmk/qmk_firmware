ifeq ($(LFK_REV), A)
    MCU = at90usb1286
else
    MCU = at90usb646
endif

ifeq ($(strip $(ISSI_ENABLE)), yes)
    OPT_DEFS += -DISSI_ENABLE
endif

ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
    OPT_DEFS += -DWATCHDOG_ENABLE
endif
