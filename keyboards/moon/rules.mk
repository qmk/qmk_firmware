# custom matrix setup
CUSTOM_MATRIX = yes

VPATH += drivers/gpio
SRC += pca9555.c matrix.c
I2C_DRIVER_REQUIRED = yes
