CUSTOM_MATRIX = lite

VPATH += drivers/gpio
SRC += pca9555.c matrix.c
QUANTUM_LIB_SRC += i2c_master.c