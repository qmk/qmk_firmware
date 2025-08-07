ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += oled.c
endif
