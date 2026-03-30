# common rules for nuphy keyboards

# LED driver
SRC += common/led_drivers/is31fl3733_side.c
SRC += common/side_effects.c

# common nuphy files
SRC += common/features/socd_cleaner.c common/rf_driver.c common/rf_queue.c common/rf.c
SRC += common/mcu_pwr.c common/sleep.c
SRC += common/keyboard.c common/keys.c common/links.c common/timer.c
SRC += common/debounce.c
SRC += common/config.c common/via.c

# keyboard-specific
SRC += user_kb.c
SRC += side.c

UART_DRIVER_REQUIRED = yes

OPT ?= 2
CUSTOM_MATRIX = lite
SRC += matrix.c

SLEEP_LED_ENABLE = no
I2C_DRIVER_REQUIRED = yes