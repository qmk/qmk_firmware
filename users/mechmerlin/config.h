#pragma once

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_ANIMATIONS
#endif // RGBLIGHT_ENABLE

#ifdef AUDIO_CLICKY
    #define AUDIO_CLICKY_ON
    #define AUDIO_CLICKY_FREQ_DEFAULT 261.63f
    #define AUDIO_CLICKY_FREQ_MIN 65.41f
    #define AUDIO_CLICKY_FREQ_MAX 1046.5f
    //#define AUDIO_CLICKY_FREQ_FACTOR 1.18921f
    //#define AUDIO_CLICKY_FREQ_FACTOR 2.71828f  // e
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

#elif defined(KEYBOARD_clueboard_66_hotswap_gen1)
    #ifndef AUDIO_CLICKY
        #define AUDIO_CLICKY
    #endif
#else
    #ifndef RGBLIGHT_ENABLE
        #define RGBLIGHT_ENABLE
    #endif
#endif
