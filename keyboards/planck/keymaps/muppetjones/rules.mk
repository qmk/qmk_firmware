ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
