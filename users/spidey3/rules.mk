
SRC += init.c
SRC += debug.c
SRC += unicode.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  # Include my fancy rgb functions source here
  SRC += rgb_caps_lock.c
endif
