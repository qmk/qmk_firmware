CUSTOM_ONESHOT_ENABLE ?= no
ifeq ($(strip $(CUSTOM_ONESHOT_ENABLE)), yes)
    SRC += $(USER_PATH)/features/oneshot.c
    OPT_DEFS += -DCUSTOM_ONESHOT_ENABLE
endif
