SRC += common/led_drivers/ws2812_side.c
SRC += common/side_effects.c
SRC += side.c side_logo.c

SRC += gem80-common.c

UART_DRIVER_REQUIRED = yes

OPT ?= 2
CUSTOM_MATRIX = lite
SRC += matrix.c

SLEEP_LED_ENABLE = no
