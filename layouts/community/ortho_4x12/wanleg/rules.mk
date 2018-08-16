AUDIO_ENABLE = no

###this if sequence below is not working####
ifeq ($(strip $(KEYBOARD)), lets_split_rev2)
	SWAP_HANDS_ENABLE = yes
elif ($(strip $(KEYBOARD)), jj40)
	SWAP_HANDS_ENABLE = no
endif