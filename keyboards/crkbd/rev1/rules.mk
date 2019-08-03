RGB_MATRIX_SPLIT_RIGHT = no  # if no, order LEDs for left hand, if yes, order LEDs for right hand

ifeq ($(strip $(RGB_MATRIX_SPLIT_RIGHT)), yes)
    OPT_DEFS += -DRGB_MATRIX_SPLIT_RIGHT
endif

SRC += 	matrix.c \
		split_util.c \
		split_scomm.c
