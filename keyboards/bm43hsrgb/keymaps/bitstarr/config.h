#pragma once

#define UNICODE_SELECTED_MODES UC_WINC, UC_WIN, UC_LNX, UC_OSX
#define UNICODE_CYCLE_PERSIST false

#ifdef RGB_DI_PIN
/*== all animations enable ==*/
    #undef RGBLIGHT_ANIMATIONS
// /*== or choose animations ==*/
    // #define RGBLIGHT_EFFECT_BREATHING
//     #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//     #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//     #define RGBLIGHT_EFFECT_SNAKE
//     #define RGBLIGHT_EFFECT_KNIGHT
//     #define RGBLIGHT_EFFECT_CHRISTMAS
//     #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//     #define RGBLIGHT_EFFECT_RGB_TEST
//     #define RGBLIGHT_EFFECT_ALTERNATING
#endif