ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
MOUSEKEY_ENABLE = yes
AUDIO_ENABLE = yes
