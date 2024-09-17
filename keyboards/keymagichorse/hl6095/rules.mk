MAKEFLAGS= -j 10
UART_DRIVER_REQUIRED = yes
USB_WAIT_FOR_ENUMERATION = no
OPT_DEFS += -DNO_USB_STARTUP_CHECK
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE




SRC+= rtt/SEGGER_RTT.c
SRC+= rtt/SEGGER_RTT_printf.c


SRC+= battery.c
SRC+= lpm_stm32f4.c

VPATH += keyboards/keymagichorse/hl6095
VPATH += keyboards/keymagichorse/hl6095/rtt
