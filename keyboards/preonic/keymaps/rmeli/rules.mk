TAP_DANCE_ENABLE = yes
AUTO_SHIFT_ENABLE = no

MAGIC_ENABLE = yes

UNICODEMAP_ENABLE = yes

# Turn off rev3_drop options
RGBLIGHT_ENABLE = no
MOUSEKEY_ENABLE = no

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
