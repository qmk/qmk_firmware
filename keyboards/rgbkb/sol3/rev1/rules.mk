# Touch encoder needs
VPATH += keyboards/rgbkb/common
SRC += touch_encoder.c
SRC += common_oled.c
I2C_DRIVER_REQUIRED = yes

SERIAL_DRIVER = usart
OPT = 3
