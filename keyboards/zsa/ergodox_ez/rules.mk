
CUSTOM_MATRIX = lite

#project specific files
SRC += matrix.c \
	   led_i2c.c

QUANTUM_LIB_SRC += i2c_master.c

MOUSE_SHARED_EP = no

DEFAULT_FOLDER = zsa/ergodox_ez/m32u4/base
