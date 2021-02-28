CUSTOM_MATRIX = yes

SRC += 	matrix.c \
		split_util.c \
		split_scomm.c

QUANTUM_LIB_SRC += i2c.c serial.c

# Disable unsupported hardware
BACKLIGHT_SUPPORTED = no
