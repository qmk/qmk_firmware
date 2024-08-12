UART_DEBUG ?= no

ifeq ($(strip $(UART_DEBUG)), yes)
    SENDCHAR_DRIVER = uart
endif
