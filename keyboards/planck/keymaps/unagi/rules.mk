ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
TAP_DANCE_ENABLE = yes
