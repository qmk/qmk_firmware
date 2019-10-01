AUDIO_ENABLE = no
SWAP_HANDS_ENABLE = no

ifeq ($(strip $(KEYBOARD)), lets_split/rev2)
	SWAP_HANDS_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), planck/rev6)
	AUDIO_ENABLE = yes
endif