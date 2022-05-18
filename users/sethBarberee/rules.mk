SRC += sethBarberee.c

# Add in custom tap dances when tap dance is enabled
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tap_dance.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	SRC += rgb_light.c
endif
