include keyboards/zsa/common/features.mk
ifeq ($(RGBLIGHT_ENABLE),yes)
    RGBLIGHT_DRIVER = custom
    WS2812_DRIVER_REQUIRED = yes
    SRC += rgblight_custom.c
endif
