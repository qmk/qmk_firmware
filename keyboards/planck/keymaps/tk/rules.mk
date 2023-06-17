ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

COMMAND_ENABLE = no

AUDIO_ENABLE = yes

ENCODER_ENABLE = yes

MOUSEKEY_ENABLE = yes

DYNAMIC_MACRO_ENABLE = yes
