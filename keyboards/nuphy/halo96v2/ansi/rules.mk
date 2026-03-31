# common rules for nuphy keyboards

# LED driver
SRC += common/led_drivers/is31fl3763_side.c
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

# LED driver path
COMMON_VPATH += $(DRIVER_PATH)/led/issi
SRC += is31fl3763.c
