MAKEFLAGS= -j 10

# SRC+= km_common/rtt/SEGGER_RTT.c
# SRC+= km_common/rtt/SEGGER_RTT_printf.c
# VPATH += keyboards/keymagichorse/km_common/rtt

ifeq ($(strip $(KB_CHECK_BATTERY_ENABLED)), yes)
 	OPT_DEFS += -DKB_CHECK_BATTERY_ENABLED
	SRC+= km_common/battery.c
endif   

ifeq ($(strip $(KB_LPM_ENABLED)), yes)
    OPT_DEFS += -DKB_LPM_ENABLED
	SRC+= km_common/lpm_stm32f4.c
endif


VPATH += keyboards/keymagichorse/km_common/

