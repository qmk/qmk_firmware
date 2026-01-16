CUSTOM_MATRIX = lite

UART_DRIVER_REQUIRED = yes

# Project specific files
SRC += matrix.c \
       common/bitc_led.c \
       big_led.c \
       common/remote_kb.c
