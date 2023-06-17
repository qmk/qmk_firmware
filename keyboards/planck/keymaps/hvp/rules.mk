ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

RGBLIGHT_ENABLE = no
TAP_DANCE_ENABLE = yes