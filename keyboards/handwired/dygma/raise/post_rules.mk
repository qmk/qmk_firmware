ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	SRC += leds.c
endif
