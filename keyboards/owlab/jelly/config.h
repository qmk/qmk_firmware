
#ifndef CONFIG_H
#define CONFIG_H
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter*/
#define VENDOR_ID       0x4F53  //0x4F53 OS for owl studio
#define PRODUCT_ID      0x4A53  //0x4A4C JL for jelly, 0x4A53 JS for jelly solder
#define DEVICE_VER      0x0001 
#define MANUFACTURER    OwLab 
#define PRODUCT         JELLY
#define DESCRIPTION     A custom 75% Keyboard by OwLab


#define MATRIX_ROWS 6
#define MATRIX_COLS 14


#define MATRIX_ROW_PINS { B0, B1, B2, B3, A15, B10 }
#define MATRIX_COL_PINS { A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, B11, B8, B9, C13 }


/* NKRO */
#ifdef NKRO_ENABLE
#         define FORCE_NKRO
#endif


#ifdef RGB_MATRIX_ENABLE

#    define USE_I2CV2
#    define DRIVER_ADDR_1 0b0110000
#    define DRIVER_ADDR_2 0b0110000
#    define DRIVER_COUNT 2
#    define DRIVER_1_LED_TOTAL 30
#    define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL //+DRIVER_2_LED_TOTAL)

#    define RGB_MATRIX_DISABLE_KEYCODES   
#    define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects

#    define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_LED_PROCESS_LIMIT 4
#    define RGB_MATRIX_LED_FLUSH_LIMIT 26
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 
#    define RGB_MATRIX_STARTUP_VAL     128 



#endif






#define RGB_DI_PIN B15

// #define WS2812_SPI SPID2
// #define WS2812_SPI_MOSI_PAL_MODE 5

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS

#define RGBLED_NUM 24  //24 , 30 
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 10
#define RGBLIGHT_LIMIT_VAL 255    


#endif




#define DIODE_DIRECTION COL2ROW


#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
     keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)
#endif