# pragma once

/* Select hand configuration */
#define MASTER_LEFT

#define TAPPING_TERM 200

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Comment this definition out if you want the main display to be output in horizontal mode */
#define OLED_VERTICAL

#ifdef RGB_MATRIX_ENABLE
    // #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
    // #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
    // #define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
    #define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
    // #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    // #define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
    // #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
    // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 10

    /* BEGIN: Disable RGB Effects */
    // #define DISABLE_RGB_MATRIX_SOLID_COLOR
     #define DISABLE_RGB_MATRIX_ALPHAS_MODS
     #define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    //  #define DISABLE_RGB_MATRIX_BREATHING
    #define DISABLE_RGB_MATRIX_BAND_SAT
    #define DISABLE_RGB_MATRIX_BAND_VAL
    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    #define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    #define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    #define DISABLE_RGB_MATRIX_CYCLE_ALL
    #define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
    #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL

    /* BEGIN: RGB_MATRIX_FRAMEBUFFER_EFFECTS */
    #define DISABLE_RGB_MATRIX_TYPING_HEATMAP
    #define DISABLE_RGB_MATRIX_DIGITAL_RAIN
    /* END: RGB_MATRIX_FRAMEBUFFER_EFFECTS */

    /* BEGIN: RGB_MATRIX_KEYPRESSES */
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    #define DISABLE_RGB_MATRIX_SPLASH
    #define DISABLE_RGB_MATRIX_MULTISPLASH
    #define DISABLE_RGB_MATRIX_SOLID_SPLASH
    #define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
    /* END: RGB_MATRIX_KEYPRESSES */

    /* END: Disable RGB Effects */
#endif
