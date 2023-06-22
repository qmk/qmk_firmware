#pragma once

// Expect to get errors if you comment a feature out and leave it in your keymap.
#define USE_BABLPASTE

#ifdef USE_BABLPASTE

#ifdef RGBLIGHT_ENABLE
#define BABL_LED_INDEX 0 // set to 0 to set all LEDs , or set to # of LED to be used as BABL updaters
#define RGBLIGHT_COLOR_MS 0x00,0x27,0x88 // blue screen?
#define RGBLIGHT_COLOR_MAC 0xF0,0xF0,0xF0 // grey
#define RGBLIGHT_COLOR_LINUX 0xF4,0xAA,0x90 // ubuntu orange?
#define RGBLIGHT_COLOR_EMACS 0x00,0x00,0x00
#define RGBLIGHT_COLOR_VI 0x00,0x90,0x00
#define RGBLIGHT_COLOR_READMUX 0x33,0xFF,0x33 // green screen
#define RGBLIGHT_COLOR_CHROMEOS 0xf4,0xc2,0xd // google yellows
#endif

#endif // bablpaste



// place overrides here
#define RGBLED_NUM 2
#define RGBLIGHT_LIMIT_VAL 200
#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_COLOR_LAYER_0 0x00, 0xFF, 0x00 // qwerty
#define RGBLIGHT_COLOR_LAYER_1 0x00, 0x99, 0x99 // cdh
#define RGBLIGHT_COLOR_LAYER_2 0xFF, 0x00, 0x00  // symbol
#define RGBLIGHT_COLOR_LAYER_3 0x00, 0xFF, 0xFF  // move
#define RGBLIGHT_COLOR_LAYER_4 0xFF, 0x00, 0xFF  // delmove
#define RGBLIGHT_COLOR_LAYER_5 0x00, 0xFF, 0xFF
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
#define RGB_LIGHT_EFFECT_BREATHE_MAX 200
#define RGBLIGHT_RAINBOW_SWIRL_RANGE 127
#endif // rgblight

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define RETRO_TAPPING
//#define PERMISSIVE_HOLD
