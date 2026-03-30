# common rules for nuphy keyboards
SRC += common/led_drivers/ws2812_side.c
SRC += common/side_effects.c
SRC += side.c side_right.c

# common nuphy files
SRC += common/mcu_pwr.c common/sleep.c
SRC += common/keyboard.c common/keys.c common/links.c common/timer.c
SRC += common/debounce.c
SRC += common/config.c common/via.c

# keyboard-specific
SRC += user_kb.c

UART_DRIVER_REQUIRED = yes

OPT ?= 2
CUSTOM_MATRIX = lite
SRC += matrix.c

SLEEP_LED_ENABLE = no
