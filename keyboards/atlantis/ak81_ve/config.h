#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x414B
#define PRODUCT_ID      0x0051
#define DEVICE_VER      0x0001
#define MANUFACTURER    Atlantis
#define PRODUCT         AK81_VE
#define DESCRIPTION     Atlantis AK81_VE

/* Key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

/* Key matrix pins */
#define MATRIX_ROW_PINS { F1, F7, F6, F5, F4, D5 }
#define MATRIX_COL_PINS { F0, C7, C6, B6, B5, B4, D7, D6, B2, B7, D3, D2, D1, D0, B3 }
#define UNUSED_PINS

/* Encoder pins */
#define ENCODERS_PAD_A { B0 }
#define ENCODERS_PAD_B { E6 }
#define ENCODER_RESOLUTION 2
#define ENCODERS 1
#define ENCODERS_CCW_KEY { { 3, 5 } } // Note:  array is { col, row )
#define ENCODERS_CW_KEY  { { 4, 5 } } // Note:  array is { col, row )

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
#define FORCE_NKRO

#define RGB_DI_PIN B1
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LAYERS

#define RGBLED_NUM 129
#define RGBLIGHT_DEFAULT_HUE 170
#define RGBLIGHT_DEFAULT_SAT 255
#define RGBLIGHT_LIMIT_VAL 170
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#endif