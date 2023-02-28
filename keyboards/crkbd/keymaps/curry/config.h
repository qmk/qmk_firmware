#pragma once

#define EE_HANDS
#define USE_SERIAL_PD2

#define OLED_DISABLE_TIMEOUT
#define TAPPING_TERM_PER_KEY

#if defined(RGB_MATRIX_ENABLE)
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120  // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 5
#    define RGB_MATRIX_SPD_STEP 10
#endif

//  comment out unnecessary layouts
#define ENABLE_QWERTY
#define ENABLE_COLEMAK
#define ENABLE_DVORAK
#define ENABLE_WORKMAN
