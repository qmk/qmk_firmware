#pragma once

#define MASTER_LEFT

//#define SSD1306OLED  //removed to use crkbd legacy driver

#define USE_SERIAL_PD2

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLED_NUM 27
//    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 5
    #define RGBLIGHT_SAT_STEP 5
    #define RGBLIGHT_VAL_STEP 17
#endif

#define RGBLIGHT_SLEEP

#ifdef COMBO_ENABLE
#    define COMBO_COUNT 1
#    define COMBO_TERM 180
#endif

#define OLED_TIMEOUT 10000

#define UNICODE_SELECTED_MODES UC_WINC, UC_MAC, UC_LNX

#define UNICODE_CYCLE_PERSIST false

#ifdef AUTO_SHIFT_ENABLE
  #define AUTO_SHIFT_MODIFIERS
  #define AUTO_SHIFT_TIMEOUT 170
  #define NO_AUTO_SHIFT_SPECIAL
  #define NO_AUTO_SHIFT_NUMERIC
#endif

#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif

#ifndef NO_DEBUG
#define NO_DEBUG
#endif

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif

#define OLED_FONT_H "keyboards/crkbd/keymaps/waffle/glcdfont.c"

#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_TERM 200

#define NO_ACTION_ONESHOT
