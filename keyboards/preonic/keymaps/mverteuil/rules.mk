ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

AUDIO_ENABLE = yes
MIDI_ENABLE = yes
TAP_DANCE_ENABLE = yes
