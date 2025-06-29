# common rules for nuphy keyboards
SRC += common/features/socd_cleaner.c common/rf_driver.c common/rf_queue.c common/rf.c
SRC += debounce.c

SRC += user_kb.c
SRC += side.c side_driver.c side_right.c

# can be separated with needed fields implemented in ansi.h
SRC += mcu_pwr.c sleep.c

UART_DRIVER_REQUIRED = yes

OPT ?= 2
CUSTOM_MATRIX = lite
SRC += matrix.c

SLEEP_LED_ENABLE = no
