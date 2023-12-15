
CUSTOM_OLED_DRIVER ?= yes
ifeq ($(strip $(OLED_ENABLE)), yes)
    ifeq ($(strip $(CUSTOM_OLED_DRIVER)), yes)
        OPT_DEFS += -DCUSTOM_OLED_DRIVER
        SRC += $(USER_PATH)/oled/oled_stuff.c
    endif
    ifeq ($(strip $(OLED_DISPLAY_TEST)), yes)
        OPT_DEFS += -DOLED_DISPLAY_TEST
    endif
endif
DEFERRED_EXEC_ENABLE = yes
