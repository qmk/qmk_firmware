DYNAMIC_MACRO_ENABLE = yes

ifeq ($(strip $(KEYBOARD)), planck/rev5)
	AUDIO_ENABLE = yes
	BACKLIGHT_ENABLE = yes
endif
