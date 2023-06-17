ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

ENCODER_ENABLE        = no

OPT_DEFS += -DTRILAYER_ENABLED
OPT_DEFS += -DAUDIO_CLICKY
