ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
LEADER_ENABLE = yes
TAP_DANCE_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
