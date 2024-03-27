SRC += mcu_pwr.c
SRC += rf.c sleep.c rf_driver.c user_kb.c rf_queue.c
SRC += side.c side_driver.c side_logo.c


# enable some features
# AUTOCORRECT_ENABLE = yes

UART_DRIVER_REQUIRED = yes
# DEBOUNCE_TYPE = asym_eager_defer_pk
DEBOUNCE_TYPE = sym_eager_pk

# CAPS_WORD_ENABLE = yes

LTO_ENABLE = yes
# CONSOLE_ENABLE = yes
