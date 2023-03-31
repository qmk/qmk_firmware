#pragma once


#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROW_PINS {B0, B3, B2, B1, F5}
#define MATRIX_COL_PINS {E6, F4, B7, D5, D3, D2, F6, F7, C7, C6, B6, B5, B4, D7, D6, D4}
#define RGBLED_NUM 20     // Number of LEDs

#define BACKLIGHT_PWM_MAP {8, 16, 40, 55, 70, 128, 200, 255}

#define RGB_DI_PIN C7  // Have to set it to something to get the ws2812 code to compile
#define RGBLED_NUM 20     // Number of LEDs
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
