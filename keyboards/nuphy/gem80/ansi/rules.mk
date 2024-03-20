SRC += rf.c sleep.c rf_driver.c user_kb.c rf_queue.c
SRC += side.c side_driver.c side_logo.c

UART_DRIVER_REQUIRED = yes
CONSOLE_ENABLE=yes
NKRO_ENABLE=yes
DEBOUNCE_TYPE = asym_eager_defer_pk

