# Enable RGB underglow
# https://beta.docs.qmk.fm/features/feature_rgblight
RGBLIGHT_ENABLE = yes # +5500 bytes
ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  # Include my fancy rgb functions source here
  SRC	 += rgb.c
endif

# Disable backlight, since I use RGB underglow.
# https://beta.docs.qmk.fm/features/feature_backlight
BACKLIGHT_ENABLE = no

# Control piezo speaker on C6
AUDIO_ENABLE = yes # +4000 bytes
