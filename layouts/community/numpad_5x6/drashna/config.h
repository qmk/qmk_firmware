#pragma once

// #define B6_AUDIO

#if defined(RGBLIGHT_ENABLE) && !defined(RGBLED_NUM)
#define RGB_DI_PIN B1
#define RGBLED_NUM 16     // Number of LEDs

#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#define RGBLIGHT_EFFECT_BREATHE_CENTER 1
#endif // RGBLIGHT_ENABLE

#if defined(KEYBOARD_primekb_prime_m)
#undef PRODUCT
#define PRODUCT Drashna Hacked Prime_M Macro Pad
#endif
