SRC += user_kb.c
SRC += rf.c
SRC += side.c

# can be separated with needed fields implemented in ansi.h
SRC += mcu_pwr.c sleep.c debounce.c rf_driver.c rf_queue.c

UART_DRIVER_REQUIRED = yes

OPT ?= 2
# initial release without custom matrix
# CUSTOM_MATRIX = lite
# SRC += matrix.c

# CONSOLE_ENABLE = yes

SRC += common/features/socd_cleaner.c
SLEEP_LED_ENABLE = no
# RGB driver
COMMON_VPATH += $(DRIVER_PATH)/led/issi
SRC += is31fl3763.c
I2C_DRIVER_REQUIRED = yes
