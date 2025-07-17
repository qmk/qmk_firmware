I2C_DRIVER_REQUIRED = yes
LIB_SRC += i2clib.c

LIB_SRC += kb_config.c

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom
LIB_SRC += drivers/modular_adns5050.c

LIB_SRC += drivers/encoder_dynamic_res.c
