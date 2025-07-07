# custom matrix setup
CUSTOM_MATRIX = lite

VPATH += drivers/gpio
SRC += pca9555.c matrix.c
I2C_DRIVER_REQUIRED = yes
