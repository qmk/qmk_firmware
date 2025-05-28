CUSTOM_MATRIX    = lite
I2C_DRIVER_REQUIRED = yes

SRC += matrix.c

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    WS2812_DRIVER_REQUIRED = yes
    RGBLIGHT_DRIVER = custom
    SRC += keyboards/zsa/ergodox_ez/rgblight_custom.c
endif
