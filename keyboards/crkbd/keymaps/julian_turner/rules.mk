RGBLIGHT_ENABLE = yes

OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
WPM_ENABLE = yes


# Enables Link Time Optimization (LTO) when compiling the keyboard. This makes the process take longer, but it can significantly reduce the compiled size (and since the firmware is small, the added time is not noticeable).
LTO_ENABLE      = yes



ifeq ($(OLED_ENABLE),yes)
	SRC += ./oled.c
endif
