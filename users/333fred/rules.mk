SRC += 333fred.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  SRC += rgb.c
endif

TAP_DANCE_ENABLE=yes
NKRO_ENABLE = yes
PERMISSIVE_HOLD = yes
LTO_ENABLE = yes
