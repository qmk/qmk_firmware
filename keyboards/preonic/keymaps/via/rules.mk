ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif 

VIA_ENABLE = yes
LTO_ENABLE = yes
