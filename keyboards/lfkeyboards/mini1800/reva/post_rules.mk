ifeq ($(strip $(WATCHDOG_ENABLE)), yes)
    OPT_DEFS += -DWATCHDOG_ENABLE
endif
