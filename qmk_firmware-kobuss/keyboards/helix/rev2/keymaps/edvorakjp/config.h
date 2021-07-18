#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#define SWAP_SCLN

#undef TAPPING_FORCE_HOLD
#undef TAPPING_TERM
#define TAPPING_TERM 300
#define IGNORE_MOD_TAP_INTERRUPT

// If you need more program area, try select and reduce rgblight modes to use.

// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
   //#define RGBLIGHT_EFFECT_BREATHING
   //#define RGBLIGHT_EFFECT_RAINBOW_MOOD
   //#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   //#define RGBLIGHT_EFFECT_SNAKE
   //#define RGBLIGHT_EFFECT_KNIGHT
   //#define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#endif

#endif /* CONFIG_USER_H */
