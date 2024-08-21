MAKEFLAGS= -j 10
UART_DRIVER_REQUIRED = yes
USB_WAIT_FOR_ENUMERATION = no


VPATH += keyboards/keymagichorse/hl6095
SRC+= lpm_stm32f4.c
