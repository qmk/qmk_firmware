#pragma once

// Tapping term settings
#define TAPPING_TERM_PER_KEY
#define TAP_HOLD_CAPS_DELAY 350
#define BOOTMAGIC_KEY_SALT KC_BSPACE
#define BOOTMAGIC_KEY_EEPROM_CLEAR KC_Q

// OLED settings
#define OLED_FONT_H "users/tominabox1/doug.c"
#define OLED_DISABLE_TIMEOUT

#define DEBOUNCE 5

// Setup RGB settings for the Dimple.
#ifdef KEYBOARD_lazydesigners_dimple
  #ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLED_NUM 50
    #define RGBLIGHT_ANIMATIONS
    #define RGBLIGHT_SLEEP
  #endif // RGBLIGHT_ENABLE

  #ifdef RGB_MATRIX_ENABLE
  #undef RGBLED_NUM
  #define RGBLED_NUM 50
  #define DRIVER_LED_TOTAL RGBLED_NUM
  #endif // RGBL_MATRIX_ENABLE
#endif // KEYBOARD_lazydesigners_dimple

// RGB_Matrix settings
#ifdef RGB_MATRIX_ENABLE
  #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
  #define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
  #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
  #define RGB_MATRIX_HUE_STEP 8
  #define RGB_MATRIX_SAT_STEP 8
  #define RGB_MATRIX_VAL_STEP 8
  #define RGB_MATRIX_SPD_STEP 10
  #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
  /* Disable the animations you don't want/need.  You will need to disable a good number of these
    because they take up a lot of space.  Disable until you can successfully compile your firmware. */
  // #define DISABLE_RGB_MATRIX_ALPHAS_MODS
  // #define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
  #define DISABLE_RGB_MATRIX_BREATHING
  // #define DISABLE_RGB_MATRIX_CYCLE_ALL
  // #define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
  // #define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
  // #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
  // #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
  #define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
  #define DISABLE_RGB_MATRIX_DUAL_BEACON
  #define DISABLE_RGB_MATRIX_RAINBOW_BEACON
  #define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
  // #define DISABLE_RGB_MATRIX_RAINDROPS
  #define DISABLE_RGB_MATRIX_JELLYBEN_RAINDROPS
  // # define DISABLE_RGB_MATRIX_TYPING_HEATMAP
  #define DISABLE_RGB_MATRIX_DIGITAL_RAIN
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
  // #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
  // #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
  // #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
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
