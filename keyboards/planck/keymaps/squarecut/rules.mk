ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
AUDIO_ENABLED = yes