OLED_ENABLE = yes
WPM_ENABLE = yes
VIA_ENABLE = yes

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled_display.c
endif
