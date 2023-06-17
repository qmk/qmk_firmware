ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
EXTRAKEY_ENABLE = no
CONSOLE_ENABLE = no
