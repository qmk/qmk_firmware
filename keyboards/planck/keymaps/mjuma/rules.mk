ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
DYNAMIC_MACRO_ENABLE = yes
TAP_DANCE_ENABLE = yes
