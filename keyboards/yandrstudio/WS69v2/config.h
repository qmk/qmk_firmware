//#ifndef CONFIG_H
//#define CONFIG_H
#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAA5
#define DEVICE_VER      0x0001
#define MANUFACTURER    lkaillAndBiu
#define PRODUCT         WS69v2

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
#define MATRIX_ROW_PINS { C13, B7, B6, C14, B8}
#define MATRIX_COL_PINS { A15, B3, B4, B5,  B9,  B14, B13, A3, A4, A5, A6,  A7,  B0, B1, A8}
#define DIODE_DIRECTION COL2ROW //ROW2COL
#define DEBOUNCE 1
#define FORCE_NKRO

/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE
#define RGB_DI_PIN B15
#define RGBLED_NUM 72
#define DRIVER_LED_TOTAL RGBLED_NUM

#define WS2812_SPI SPID2 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 5


#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGBLIGHT_VAL_STEP 10
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 10
#define RGB_DISABLE_WHEN_USB_SUSPENDED true
#define RGB_MATRIX_CENTER { 32, 96 }
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#endif


