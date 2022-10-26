ifeq ($(strip $(FADER_ENABLE)$(MIDI_ENABLE)),yesyes)
	OPT_DEFS += -DFADER_ENABLE
	SRC += \
		ads1100.c \
		fader.c
endif