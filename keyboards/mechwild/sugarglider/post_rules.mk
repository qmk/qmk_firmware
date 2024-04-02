# Checking if WIDE_OLED
ifeq ($(strip $(WIDE_OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_DISPLAY_128X64
endif
