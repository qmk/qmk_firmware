
# 是否使能低功耗
KB_LPM_ENABLED = yes
# 是否使能QMK端读取电池电压
KB_CHECK_BATTERY_ENABLED = no
# 打开QMK的ADC读取功能
ANALOG_DRIVER_REQUIRED = no
# 开启键盘层DEBUG  这里是用RTT输出日记的
KM_DEBUG = no

ifeq ($(strip $(KB_CHECK_BATTERY_ENABLED)), yes)
 	OPT_DEFS += -DKB_CHECK_BATTERY_ENABLED
endif   

include keyboards/keymagichorse/km_common/km_common.mk

VIA_ENABLE = yes
