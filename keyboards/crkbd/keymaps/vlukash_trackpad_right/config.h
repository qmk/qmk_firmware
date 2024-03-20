#pragma once

#define NO_DEBUG_LEDS

// Connector PCB version
// 1 - PCB that supports flex caple and the trackpad sensor is mounted on an 'H' keycap
//   - https://github.com/vlukash/corne-trackpad/tree/master/connector
// 2 - PCB woth no flex option, track sensor mounted directly on the PCB
//   - https://github.com/vlukash/corne-trackpad/tree/master/connector-no-flex
#define TRACKPAD_CONNECTOR_VER 1

/* Select hand configuration */
#define MASTER_RIGHT

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 300

#undef RGBLED_NUM
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
#define RGBLED_NUM 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

/* key matrix size */
// Rows are doubled-up
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { F4, F5, F6, F7, B7, D5 }

/* ws2812 RGB LED */
#undef RGB_DI_PIN
#define RGB_DI_PIN B5
