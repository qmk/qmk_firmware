ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += keyboards/mechboards/common/display_oled.c
endif
