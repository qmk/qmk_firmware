SRC += brandonschlack.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += rgb_bs.c
endif

RGB_MATRIX_ENABLE ?= no
ifneq ($(strip $(RGB_MATRIX_ENABLE)), no)
    SRC += rgb_bs.c
endif
