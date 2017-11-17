include keyboards/lets_split/rules.mk
include keyboards/lets_split/rev2/rules.mk
COMMON_VPATH := keyboards/lets_split $(COMMON_VPATH)

RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.