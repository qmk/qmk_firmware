ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

BACKLIGHT_ENABLE  = no
LEADER_ENABLE = yes
ENCODER_ENABLE = yes
MOUSEKEY_ENABLE = yes
