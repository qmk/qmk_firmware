ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    WS2812_DRIVER_REQUIRED = yes
    RGBLIGHT_DRIVER = custom
    SRC += keyboards/zsa/ergodox_ez/rgblight_custom.c
endif
