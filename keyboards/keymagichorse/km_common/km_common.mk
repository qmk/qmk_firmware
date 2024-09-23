OPT_DEFS += -DKM_DEBUG

MAKEFLAGS= -j 10
UART_DRIVER_REQUIRED = yes
USB_WAIT_FOR_ENUMERATION = no
OPT_DEFS += -DNO_USB_STARTUP_CHECK
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE


SRC+= km_common/rtt/SEGGER_RTT.c
SRC+= km_common/rtt/SEGGER_RTT_printf.c
VPATH += keyboards/keymagichorse/km_common/rtt


SRC+= km_common/battery.c
SRC+= km_common/lpm_stm32f4.c

VPATH += keyboards/keymagichorse/km_common/

