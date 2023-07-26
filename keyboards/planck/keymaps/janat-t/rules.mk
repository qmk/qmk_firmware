ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif

TERMINAL_ENABLE = yes
MIDI_ENABLE = yes
CAPS_WORD_ENABLE = yes
