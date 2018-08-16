AUDIO_ENABLE = no
SWAP_HANDS_ENABLE = yes

###this if sequence below is not working####
ifeq ($(strip $(KEYBOARD)), jj40)
	SWAP_HANDS_ENABLE = no
endif
