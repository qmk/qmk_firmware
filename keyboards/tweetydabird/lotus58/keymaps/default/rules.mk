ENCODER_MAP_ENABLE = yes
AUTO_SHIFT_ENABLE = yes

ifeq ($(strip $(MCU)), atmega32u4)
	LTO_ENABLE = yes
endif
