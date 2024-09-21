ENCODER_MAP_ENABLE = yes
VIA_ENABLE = yes

ifeq ($(strip $(MCU)), atmega32u4)
    LTO_ENABLE = yes
endif
