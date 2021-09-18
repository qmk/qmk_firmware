
ifneq (,$(findstring QMK_PROTON_C,$(BOARD)))
    WS2812_DRIVER = pwm
    SERIAL_DRIVER = usart
    AUDIO_ENABLE = no
    LTO_ENABLE = no
endif
