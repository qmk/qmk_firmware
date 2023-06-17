ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
AUTO_SHIFT_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
STENO_ENABLE = yes
