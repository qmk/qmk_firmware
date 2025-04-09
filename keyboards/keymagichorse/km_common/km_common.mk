MAKEFLAGS= -j 10



# 74HC595
ifeq ($(strip $(SHIFT595_ENABLED)), yes)
    OPT_DEFS += -DSHIFT595_ENABLED
    VPATH += keyboards/keymagichorse/km_common/74hc595/
    SRC += km_common/74hc595/74hc595.c
endif

ifeq ($(strip $(KM_DEBUG)), yes)
	OPT_DEFS += -DKM_DEBUG
	SRC+= km_common/rtt/SEGGER_RTT.c
	SRC+= km_common/rtt/SEGGER_RTT_printf.c
	VPATH += keyboards/keymagichorse/km_common/rtt
endif   

# 提前导入mcu的mk
include $(wildcard $(PLATFORM_PATH)/*/mcu_selection.mk)
$(info !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!MCU_SERIES = $(MCU_SERIES))
$(info !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!MCU_LDSCRIPT = $(MCU_LDSCRIPT))

ifeq ($(strip $(KB_LPM_ENABLED)), yes)
    ifneq ($(filter $(MCU_SERIES),STM32F4xx),)
        OPT_DEFS += -DKB_LPM_ENABLED
        SRC += km_common/lpm_stm32f4.c
    endif
    ifneq ($(filter $(MCU_SERIES),STM32F1xx),)
        OPT_DEFS += -DKB_LPM_ENABLED
        SRC += km_common/lpm_stm32f1.c
    endif
endif



VPATH += keyboards/keymagichorse/km_common/

