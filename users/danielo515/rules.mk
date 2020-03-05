SRC += danielo515.c

ifeq ($(strip $(COMBO_ENABLE)), yes)
    SRC += combo.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dance.c
endif
