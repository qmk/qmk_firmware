SRC += rgb_record/rgb_record.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	SRC += rgb_record/rgb_rgblight.c
	SRC += rgb_record/rgb_effect.c
endif
