#pragma once

#define FORCE_NKRO

#define PERMISSIVE_HOLD
#define TAPPING_TERM 150

#define TAP_HOLD_CAPS_DELAY 0
#undef RGB_MATRIX_DEFAULT_MODE
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

// #undef ENABLE_RGB_MATRIX_SOLID_COLOR
// #undef ENABLE_RGB_MATRIX_ALPHAS_MODS
// #undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #undef ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_BAND_SAT
// #undef ENABLE_RGB_MATRIX_BAND_VAL
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
// #undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
// #undef ENABLE_RGB_MATRIX_SPLASH
// #undef ENABLE_RGB_MATRIX_MULTISPLASH
// #undef ENABLE_RGB_MATRIX_SOLID_SPLASH
// #undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

// #define RGB_MATRIX_KEYRELEASES

// some speed shit

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#define NO_ACTION_ONESHOT
#define TAPPING_FORCE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

// #include "config_led.h"
// #include "dz60rgb.h"
