# common rules for nuphy keyboards
SRC += common/led_drivers/ws2812_side.c
SRC += common/side_effects.c
SRC += side.c side_right.c

# keyboard-specific
SRC += user_kb.c

UART_DRIVER_REQUIRED = yes

OPT ?= 2
CUSTOM_MATRIX = lite
SRC += matrix.c

SLEEP_LED_ENABLE = no
