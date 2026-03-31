# common rules for nuphy keyboards

# LED driver
SRC += common/led_drivers/is31fl3733_side.c
SRC += common/side_effects.c

# keyboard-specific
SRC += user_kb.c
SRC += side.c

UART_DRIVER_REQUIRED = yes

OPT ?= 2
CUSTOM_MATRIX = lite
SRC += matrix.c

SLEEP_LED_ENABLE = no
I2C_DRIVER_REQUIRED = yes