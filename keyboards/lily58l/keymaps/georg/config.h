#pragma once

#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

#undef DEBOUNCE
#define DEBOUNCE 5 

#define OLED_FRAMERATE 30
#define OLED_FONT_H "common/glcdfont.c"

#ifdef RGBLIGHT_ENABLE
  // #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_EFFECT_SNAKE
  #define RGBLIGHT_HUE_STEP 3 // number of steps to cycle through the hue by
  #define RGBLIGHT_SAT_STEP 6 // number of steps to increment the saturation by
  #define RGBLIGHT_VAL_STEP 6 // number of steps to increment the brightness by

//  #define RGBLIGHT_EFFECT_RGB_TEST
  #define RGBLIGHT_SLEEP //  the RGB lighting will be switched off when the host goes to sleep
#endif

#ifdef RGB_MATRIX_ENABLE
#define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
 
#define RGB_MATRIX_KEYPRESSES
// #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
  #define RGB_MATRIX_HUE_STEP 3 // number of steps to cycle through the hue by
  #define RGB_MATRIX_SAT_STEP 6 // number of steps to increment the saturation by
  #define RGB_MATRIX_VAL_STEP 6 // number of steps to increment the brightness by

  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
  #define DISABLE_RGB_MATRIX_SPLASH
  #define DISABLE_RGB_MATRIX_SOLID_SPLASH
#endif

#define EE_HANDS

// Master is where the usb cable is plugged in
// #define MASTER_LEFT
#define MASTER_LEFT


// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
