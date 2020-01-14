#pragma once

// Tapping term settings
#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT
//#define PERMISSIVE_HOLD
//#define TAPPING_LAYER_TERM 150 // Custom LT Tapping term
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
#define IGNORE_TAPPING_FORCE_HOLD_PER_KEY

// Combos
#if defined(KEYBOARD_thevankeyboards_roadkit)
  #define COMBO_COUNT 7
  #define COMBO_TERM 75
#else //everything else
  #define COMBO_COUNT 10
  #define COMBO_TERM 100
#endif

#if defined(LED_ANIMATIONS)
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   //#define RGBLIGHT_EFFECT_SNAKE
   #define RGBLIGHT_EFFECT_KNIGHT
   //#define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#endif
#define RGBLIGHT_SLEEP

// Bootmagic
#define BOOTMAGIC_KEY_SALT KC_BSPACE
#define BOOTMAGIC_KEY_EEPROM_CLEAR KC_Q

// OLED settings
#define OLED_FONT_H "users/tominabox1/doug.c"
#define OLED_DISABLE_TIMEOUT

#ifdef KEYBOARD_treadstone32
#undef RGBLED_NUM
#define RGBLED_NUM 5
#undef RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL 255
// Selection of RGBLIGHT MODE to use.
#endif

// Setup RGB settings for the Dimple.
#ifdef KEYBOARD_lazydesigners_dimple
  #ifdef RGB_MATRIX_ENABLE
    #undef RGBLED_NUM
    #define RGBLED_NUM 50
    #define DRIVER_LED_TOTAL RGBLED_NUM
  #endif // RGBL_MATRIX_ENABLE
  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_LIMIT_VAL 150
  #define RGBLIGHT_EFFECT_BREATHE_CENTER 2.7
#endif // KEYBOARD_lazydesigners_dimple

#ifdef KEYBOARD_thevankeyboards_minivan
  #define BACKLIGHT_PIN B7
  #define BACKLIGHT_LEVELS 1
  //#define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_LIMIT_VAL 150
  //#define RGBLIGHT_EFFECT_BREATHE_CENTER 2.7
#endif // Minivan

// RGB_Matrix settings
#ifdef RGB_MATRIX_ENABLE
  #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
  // #define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
  #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
  #define RGB_MATRIX_HUE_STEP 8
  #define RGB_MATRIX_SAT_STEP 8
  #define RGB_MATRIX_VAL_STEP 8
  #define RGB_MATRIX_SPD_STEP 10
  #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
  /* Disable the animations you don't want/need.  You will need to disable a good number of these
    because they take up a lot of space.  Disable until you can successfully compile your firmware. */
  #define DISABLE_RGB_MATRIX_ALPHAS_MODS
  #define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
  #define DISABLE_RGB_MATRIX_BREATHING
  // #define DISABLE_RGB_MATRIX_CYCLE_ALL
  #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
  #define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
  #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
  #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
  #define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
  #define DISABLE_RGB_MATRIX_DUAL_BEACON
  #define DISABLE_RGB_MATRIX_RAINBOW_BEACON
  #define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
  #define DISABLE_RGB_MATRIX_RAINDROPS
  // #define DISABLE_RGB_MATRIX_JELLYBEN_RAINDROPS
  #define DISABLE_RGB_MATRIX_TYPING_HEATMAP
  #define DISABLE_RGB_MATRIX_DIGITAL_RAIN
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
  // #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
  #define DISABLE_RGB_MATRIX_SPLASH
  #define DISABLE_RGB_MATRIX_MULTISPLASH
  #define DISABLE_RGB_MATRIX_SOLID_SPLASH
  #define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif //RGB_MATRIX_ENABLE

// Hex size reduction options
#ifndef NO_DEBUG
  #define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
  #define NO_PRINT
#endif // !NO_PRINT
#define NO_ACTION_ONESHOT

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
