MAKEFLAGS= -j 10

# SRC+= km_common/rtt/SEGGER_RTT.c
# SRC+= km_common/rtt/SEGGER_RTT_printf.c
# VPATH += keyboards/keymagichorse/km_common/rtt

SRC+= km_common/battery.c
SRC+= km_common/lpm_stm32f4.c

VPATH += keyboards/keymagichorse/km_common/

