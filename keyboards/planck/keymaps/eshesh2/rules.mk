ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
ENCODER_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
