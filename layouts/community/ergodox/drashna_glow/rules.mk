USER_NAME := drashna
SRC += ../drashna/keymap.c

-include $$(LAYOUT_KEYMAP_PATH)/../drashna/rules.mk

ifneq (,$(findstring ergodox_ez,$(KEYBOARD)))
  RGBLIGHT_ENABLE = no
  RGB_MATRIX_ENABLE = yes
endif
