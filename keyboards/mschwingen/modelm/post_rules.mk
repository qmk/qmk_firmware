ifeq ($(strip $(UART_DEBUG)), yes)
    OPT_DEFS += -DUART_DEBUG
endif
