# Enable RGB if not a Planck
ifeq ($(LAYOUTS_HAS_RGB),yes)
	RGBLIGHT_ENABLE = yes
endif
AUDIO_ENABLE = yes
