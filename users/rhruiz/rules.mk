SRC += rhruiz.c

ifeq ($(strip $(RAW_ENABLE)), yes)
    SRC += raw_hid/raw_hid.c
endif

ifeq ($(strip $(OLED_ROTATE)), yes)
	OPT_DEFS += -DOLED_ROTATE -DRHRUIZ_OLED_FONT_H="\"users/rhruiz/oled/font_rotated.c\""
else
	OPT_DEFS += -DRHRUIZ_OLED_FONT_H="\"users/rhruiz/oled/glcdfont.c\""
endif

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    SRC += oled/oled.c
endif

ifeq ($(strip $(RGBLIGHT_LAYERS)), yes)
	OPT_DEFS += -DRGBLIGHT_LAYERS -DRGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
endif
