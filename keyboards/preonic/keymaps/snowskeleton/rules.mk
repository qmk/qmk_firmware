ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
