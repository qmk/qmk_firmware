# Enable RGB if not a Planck
ifeq ($(LAYOUTS_HAS_RGB),yes)
	RGBLIGHT_ENABLE = yes
endif
AUDIO_ENABLE = no
ifeq ($(strip $(KEYBOARD)), zlant)
  BACKLIGHT_ENABLE = no
else ifeq ($(strip $(KEYBOARD)), 40percentclub/4x4)
	  BACKLIGHT_ENABLE = no
else
  BACKLIGHT_ENABLE = yes
endif
