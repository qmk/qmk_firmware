#pragma once

#ifdef OLED_DRIVER_ENABLE
#    define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 150

#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#    define RGBLIGHT_DEFAULT_HUE 70   // 0-255
#    define RGBLIGHT_DEFAULT_SAT 255  // 0-255
#    define RGBLIGHT_DEFAULT_VAL 150  // 0-255

#    define RGBLIGHT_SLEEP
// #    define RGBLIGHT_ANIMATIONS    // animations disabled
#endif

// relevant for modtap on various keys
// see https://docs.qmk.fm/#/tap_hold
// #define TAPPING_TERM 4000
// #define PERMISSIVE_HOLD

// see https://docs.qmk.fm/#/feature_split_keyboard?id=hardware-configuration-options
// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
#define SPLIT_USB_DETECT
#define NO_USB_STARTUP_CHECK
