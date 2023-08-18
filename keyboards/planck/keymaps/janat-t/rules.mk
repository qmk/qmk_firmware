ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

MIDI_ENABLE = yes
CAPS_WORD_ENABLE = yes
TRI_LAYER_ENABLE = yes
