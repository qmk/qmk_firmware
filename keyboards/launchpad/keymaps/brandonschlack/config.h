#pragma once

/* Underlight Configuration */
#ifdef RGB_DI_PIN
    #undef RGB_DI_PIN
    #define RGB_DI_PIN F4
    #undef RGBLED_NUM
    #define RGBLED_NUM 2  // Number of LEDs
#endif
#define RGBLIGHT_EFFECT_BREATHING // Only have Breathing Animation
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

/* Mouse Keys Configuration */
#define MK_3_SPEED
#define MK_W_INTERVAL_UNMOD 20
