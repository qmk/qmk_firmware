# Cirque touchpad settings
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi    # Pointing Device Driver

# Custom matrix setup
CUSTOM_MATRIX = lite

VPATH += drivers/gpio
SRC += mcp23018.c matrix.c
I2C_DRIVER_REQUIRED = yes
