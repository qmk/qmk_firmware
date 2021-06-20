// RGB LED support
//#define RGBLIGHT_ANIMATIONS : see ./rules.mk: LED_ANIMATIONS = yes or no
//    see ./rules.mk: LED_BACK_ENABLE or LED_UNDERGLOW_ENABLE set yes
#ifdef RGBLIGHT_ENABLE
  #ifdef RGBLED_BACK
    #ifdef RGBLED_CONT
      #define RGBLED_NUM 48
      #define RGBLED_SPLIT { 24, 24 }
    #else
      #define RGBLED_NUM 24
    #endif
  #else
    #ifdef RGBLED_BOTH
      #ifdef RGBLED_CONT
        #define RGBLED_NUM 60
        #define RGBLED_SPLIT { 30, 30 }
//      #define RGBLIGHT_LED_MAP {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29}
      #else
        #define RGBLED_NUM 30
      #endif
    #else
      #ifdef RGBLED_CONT
        #define RGBLED_NUM 12
        #define RGBLED_SPLIT { 6, 6 }
      #else
        #define RGBLED_NUM 6
      #endif
    #endif
  #endif
#endif

#ifndef IOS_DEVICE_ENABLE
  #if (RGBLED_NUM <= 6) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 12))
    #define RGBLIGHT_LIMIT_VAL 255
  #else
    #if (RGBLED_NUM <= 16) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 32))
      #define RGBLIGHT_LIMIT_VAL 130
    #else
      #define RGBLIGHT_LIMIT_VAL 120
    #endif
  #endif
  #define RGBLIGHT_VAL_STEP 17
#else
  #if (RGBLED_NUM <= 6) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 12))
    #define RGBLIGHT_LIMIT_VAL 90
  #else
    #if (RGBLED_NUM <= 16) || (defined(RGBLED_CONT) && (RGBLED_NUM <= 32))
      #define RGBLIGHT_LIMIT_VAL 45
    #else
      #define RGBLIGHT_LIMIT_VAL 35
    #endif
  #endif
  #define RGBLIGHT_VAL_STEP 4
#endif
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17

#if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value
//  120  RGBoff
//  330  RGB 6
//  300  RGB 32
  #define USB_MAX_POWER_CONSUMPTION 400
#else
  // fix iPhone and iPad power adapter issue
  // iOS device need lessthan 100
  #define USB_MAX_POWER_CONSUMPTION 100
#endif
