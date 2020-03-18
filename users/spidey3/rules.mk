
SRC += init.c
SRC += spidey3.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
  SRC += layer_rgb.c
endif
ifeq ($(strip $(UNICODEMAP_ENABLE)), yes)
  SRC += unicode.c
endif
