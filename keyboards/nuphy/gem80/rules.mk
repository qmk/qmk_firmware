SRC += user_kb.c
SRC += rf.c
SRC += side.c side_driver.c side_logo.c

# can be separated with needed fields implemented in gem80-common.h
SRC += mcu_pwr.c sleep.c debounce.c rf_driver.c rf_queue.c

SRC += gem80-common.c

UART_DRIVER_REQUIRED = yes

OPT ?= 2
CUSTOM_MATRIX = lite
SRC += matrix.c

SRC += common/features/socd_cleaner.c
SLEEP_LED_ENABLE = no
