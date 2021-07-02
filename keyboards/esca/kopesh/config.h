#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xE5CA //esca but original design by Coumbaya
#define PRODUCT_ID      0x0351 //Kopesh
#define DEVICE_VER      0x0001
#define MANUFACTURER    esca
#define PRODUCT         kopesh
#define DESCRIPTION     30% Ortho Alice

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 8

/* key matrix pins */
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B5, B4 }
#define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6, F5, F4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define USE_I2C

/* number of backlight levels */
#define SSD1306OLED

//define BACKLIGHT_PIN D3
#ifdef  BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 16
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

//define DRIVER_LED_TOTAL 8

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLED_NUM 8
#define RGBLIGHT_LIMIT_VAL 240
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
#endif
