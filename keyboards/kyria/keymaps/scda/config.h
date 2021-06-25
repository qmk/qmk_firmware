#pragma once

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 150
#endif

// relevant for modtap on various keys
// see https://docs.qmk.fm/#/tap_hold
// #define TAPPING_TERM 4000
// #define PERMISSIVE_HOLD

// TODO: muss ich das hier deaktivieren beim flashen der zweiten Seite?
// see https://docs.qmk.fm/#/feature_split_keyboard?id=hardware-configuration-options

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
