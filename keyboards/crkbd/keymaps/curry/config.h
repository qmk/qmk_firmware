#pragma once

#define EE_HANDS
#define USE_SERIAL_PD2

#define OLED_DISABLE_TIMEOUT
#define TAPPING_TERM_PER_KEY

#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    define RGBLED_NUM 27

#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 5
#    define RGBLIGHT_LIMIT_VAL 120
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true  // turn off effects when suspended
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120  // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 5
#    define RGB_MATRIX_SPD_STEP 10
#endif
