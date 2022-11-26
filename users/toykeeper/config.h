// config.h for ToyKeeper's keymaps
#pragma once

// Scan faster than the default 125 Hz
#define USB_POLLING_INTERVAL_MS 1


///// Tap / Hold behavior /////

// configure QMK tap-hold behavior for "hold preferred" mode
#define HOLD_ON_OTHER_KEY_PRESS

// 1 tap to lock TT() keys like MouseLock, instead of 5 taps
#define TAPPING_TOGGLE 1

// tap / hold threshold
#undef  TAPPING_TERM
#define TAPPING_TERM 250  // default 200, 150 may help some things

// auto-repeat is only used on the "Any" key
#define AUTOREPEAT_DELAY 250
#define AUTOREPEAT_MS 25


///// misc settings /////

// tap both shifts to activate CapsWord
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// configure KC_GESC (I want to be able to do H-C-Esc and H-M-Esc)
#define GRAVE_ESC_ALT_OVERRIDE  // Always send Escape if Alt is pressed
#define GRAVE_ESC_CTRL_OVERRIDE // Always send Escape if Control is pressed

// OneShot keys were never timing out
#define ONESHOT_TIMEOUT 5000  // 5s


///// make the mouse more usable /////

// decelerate after key release, don't stop immediately
// (also tracks X and Y speed separately)
#define MOUSEKEY_INERTIA

// Delay between pressing a movement key and cursor movement
#undef  MOUSEKEY_DELAY
#define MOUSEKEY_DELAY	150
// Time between cursor movements in milliseconds
#undef  MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL	16  // 60 FPS = 1000/16
// Step size
#undef  MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA	1  // let me move one pixel when key is tapped
// Maximum cursor speed at which acceleration stops
#undef  MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED	32  // 1920 px / 60 fps = 32 px per frame to cross the screen in 1s
// Time until maximum cursor speed is reached
#undef  MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX	32  // frames until max speed, 32 frames / 60 FPS = roughly half a second
// Delay between pressing a wheel key and wheel movement
#undef  MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY	250  // default 300
// Time between wheel movements
#undef  MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL	40  // default 100
// Maximum number of scroll steps per scroll action
#undef  MOUSEKEY_WHEEL_MAX_SPEED
#define MOUSEKEY_WHEEL_MAX_SPEED	8  // default 8
// Time until maximum scroll speed is reached
#undef  MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX	64  // default 40


#ifdef HAS_RGB  // copy/paste this into the keymap config.h, because "HAS_RGB" can't be defined yet here

    ///// RGB stuff... /////
    // https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-lighting

    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255

    // disable backlight when USB suspended (PC sleep/hibernate/shutdown)
    #undef  RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGB_DISABLE_WHEN_USB_SUSPENDED 1

    // disable backlight after timeout in minutes, 0 = no timeout
    #define RGB_MATRIX_TIMEOUT (1000*60*5)  // 5 minutes
    #define RGB_DISABLE_TIMEOUT RGB_MATRIX_TIMEOUT

    // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
    #ifndef RGB_MATRIX_LED_COUNT
    #define RGB_MATRIX_LED_COUNT DRIVER_LED_TOTAL  // name changed 2022-11-15
    #endif
    // default: (RGB_MATRIX_LED_COUNT + 4) / 5
    // weird, it's more responsive without a limit
    #define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4)
    // limits in milliseconds how frequently an animation will update the LEDs.
    // 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
    #define RGB_MATRIX_LED_FLUSH_LIMIT 50  // default: 16

    // reactive RGB effects
    #define RGB_MATRIX_KEYPRESSES
    #undef RGB_MATRIX_KEYRELEASES

    // turn off all RGB Matrix effects, then selectively enable the ones I like
    #undef ENABLE_RGB_MATRIX_ALPHAS_MODS
    #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    #undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    #undef ENABLE_RGB_MATRIX_BAND_SAT
    #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    #undef ENABLE_RGB_MATRIX_BAND_VAL
    #undef ENABLE_RGB_MATRIX_BREATHING
    #undef ENABLE_RGB_MATRIX_CYCLE_ALL
    #undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    #undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    #undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #undef ENABLE_RGB_MATRIX_DUAL_BEACON
    #undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    #undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #undef ENABLE_RGB_MATRIX_HUE_BREATHING
    #undef ENABLE_RGB_MATRIX_HUE_PENDULUM
    #undef ENABLE_RGB_MATRIX_HUE_WAVE
    #undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    #undef ENABLE_RGB_MATRIX_MULTISPLASH
    #undef ENABLE_RGB_MATRIX_PIXEL_FLOW
    #undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
    #undef ENABLE_RGB_MATRIX_PIXEL_RAIN
    #undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
    #undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    #undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    #undef ENABLE_RGB_MATRIX_RAINDROPS
    #undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    #undef ENABLE_RGB_MATRIX_SOLID_SPLASH
    #undef ENABLE_RGB_MATRIX_SPLASH

    #define ENABLE_RGB_MATRIX_MULTISPLASH

    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_DEFAULT_MODE
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_MULTISPLASH

#endif
