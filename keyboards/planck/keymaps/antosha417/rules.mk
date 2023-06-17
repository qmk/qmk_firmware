ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
AUDIO_ENABLE = yes
COMBO_ENABLE = yes

