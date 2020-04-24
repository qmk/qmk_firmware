BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output (needs a pin configured in config.h, see docs/feature_audio.md)

ifeq ("$(KEYBOARD)","vitamins_included")
  RGBLIGHT_ENABLE = no
else ifeq ($(strip $(KEYBOARD)), 40percentclub/4x4)
	  RGBLIGHT_ENABLE = no
else
  RGBLIGHT_ENABLE = yes
endif

