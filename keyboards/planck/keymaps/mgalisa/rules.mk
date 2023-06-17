ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
EXTRAKEY_ENABLE = yes
# RGBLIGHT_ENABLE = yes
## I bought the WS2812s...
## just need the main branch to be updated.
# Uncomment to make build fail.
