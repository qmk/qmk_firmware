#pragma once

/* ws2812 RGB LED */
#if defined(KEYBOARD_fractal)
#    define RGB_DI_PIN D2
#    undef RGBLED_NUM
#    define RGBLIGHT_ANIMATIONS
#    define RGBLED_NUM 29  // Number of LEDs
#    undef RGBLIGHT_HUE_STEP
#    define RGBLIGHT_HUE_STEP 8
#    undef RGBLIGHT_SAT_STEP
#    define RGBLIGHT_SAT_STEP 8
#    undef RGBLIGHT_VAL_STEP
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 175
#    define RGBLIGHT_SLEEP

#    define RGBLIGHT_EFFECT_KNIGHT_OFFSET 3
#    define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 14
#    define B7_AUDIO
#    define NO_MUSIC_MODE
#endif
