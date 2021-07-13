OLED_DRIVER_ENABLE = yes
WPM_ENABLE = yes
VIA_ENABLE = yes

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
	SRC += oled_display.c
endif
