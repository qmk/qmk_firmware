#pragma once

#define TAP_CODE_DELAY 10

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_SLEEP
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
#endif // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif

#ifdef AUDIO_CLICKY
    #define AUDIO_CLICKY_ON
    #define AUDIO_CLICKY_FREQ_DEFAULT 261.63f
    #define AUDIO_CLICKY_FREQ_MIN 65.41f
    #define AUDIO_CLICKY_FREQ_MAX 1046.5f
    #define AUDIO_CLICKY_FREQ_FACTOR 1.61803f // golden ratio
    #define AUDIO_CLICKY_FREQ_RANDOMNESS 17.0f
#endif

// Enable features depending on keyboard
#if defined(KEYBOARD_clueboard_66_hotswap_prototype)
    #ifndef RGBLIGHT_ENABLE
        #define RGBLIGHT_ENABLE
    #endif
    #ifndef AUDIO_CLICKY
        #define AUDIO_CLICKY
    #endif
#elif defined(KEYBOARD_clueboard_66_hotswap_gen1) || defined(KEYBOARD_clueboard_66_rev4)
    #ifndef AUDIO_CLICKY
        #define AUDIO_CLICKY
    #endif
#endif
