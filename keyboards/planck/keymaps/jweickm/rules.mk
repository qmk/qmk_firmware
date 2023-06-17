CONSOLE_ENABLE = no         # Console for debug
LEADER_ENABLE = yes
TAP_DANCE_ENABLE = yes			# enable tap dance functionality

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
