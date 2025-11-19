RGB_RECORD_DIR = keyboards/epomaker/tide49/rgb_record

VPATH += $(RGB_RECORD_DIR)
SRC += $(RGB_RECORD_DIR)/rgb_record.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	SRC += $(RGB_RECORD_DIR)/rgb_rgblight.c
	SRC += $(RGB_RECORD_DIR)/rgb_effect.c
endif
