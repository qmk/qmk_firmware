ifeq ($(strip $(LED_ENABLE)), yes)
    OPT_DEFS += -DLED_ENABLE
    SRC += led_controls.c
    UART_DRIVER_REQUIRED = yes
endif
