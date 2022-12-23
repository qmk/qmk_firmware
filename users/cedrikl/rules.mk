SRC += cedrikl.c
ifeq ($(strip $(STARTUP_NUMLOCK_ON)), yes)
    OPT_DEFS += -DSTARTUP_NUMLOCK_ON
endif
