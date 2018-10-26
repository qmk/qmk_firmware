AUDIO_ENABLE = no
SWAP_HANDS_ENABLE = no

ifeq ($(strip $(KEYBOARD)), lets_split/rev2)
	SWAP_HANDS_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), planck/rev6)
	AUDIO_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), jj40)
	BACKLIGHT_ENABLE = yes
	# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
	SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
endif