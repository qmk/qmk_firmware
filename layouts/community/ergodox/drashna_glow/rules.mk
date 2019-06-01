USER_NAME := drashna

CORRECTED_LAYOUT := $(LAYOUTS_REPO)/$(LAYOUT)/drashna

SRC += $(CORRECTED_LAYOUT)/keymap.c

-include $(CORRECTED_LAYOUT)/rules.mk

ifneq (,$(findstring ergodox_ez,$(KEYBOARD)))
  RGBLIGHT_ENABLE = no
  RGB_MATRIX_ENABLE = yes
  TAP_DANCE_ENABLE  = no
endif
