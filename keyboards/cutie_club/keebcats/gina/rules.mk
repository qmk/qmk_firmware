RGBLIGHT_ENABLE = yes
CUSTOM_MATRIX = lite

SRC += matrix.c \
	indicator_leds.c \
	i2c_master.c \
	lib/i2c_helpers.c \
	lib/pcal6416a/pcal6416a.c
