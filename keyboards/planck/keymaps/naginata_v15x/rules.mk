OS_DETECTION_ENABLE = yes
CONSOLE_ENABLE = no         # Console for debug

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
