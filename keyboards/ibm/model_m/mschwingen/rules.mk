CUSTOM_MATRIX = lite

SRC += matrix.c
UART_DRIVER_REQUIRED = yes
SPI_DRIVER_REQUIRED = yes

OPT_DEFS += -DSLEEP_LED_ENABLE

DEFAULT_FOLDER = ibm/model_m/mschwingen/led_wired
