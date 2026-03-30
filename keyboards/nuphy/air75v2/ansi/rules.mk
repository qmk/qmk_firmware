# common rules for nuphy keyboards
SRC += debounce.c

SRC += user_kb.c
SRC += common/ws2812-side-driver.c
SRC += side.c side_right.c

# can be separated with needed fields implemented in ansi.h
SRC += common/mcu_pwr.c common/sleep.c

UART_DRIVER_REQUIRED = yes

OPT ?= 2
CUSTOM_MATRIX = lite
SRC += matrix.c

SLEEP_LED_ENABLE = no
