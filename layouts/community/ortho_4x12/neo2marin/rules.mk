BACKLIGHT_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes

ifeq ($(strip $(KEYBOARD)), planck/rev5)
	AUDIO_ENABLE = yes
endif
