/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#pragma once

// Xulkal custom stuff
#undef QUICK_TAP_TERM

#undef TAPPING_TERM
#define TAPPING_TERM 175

#define SPACE_CADET_MODIFIER_CARRYOVER
#define LSPO_KEYS KC_LSFT, KC_TRNS, KC_LBRC
#define RSPC_KEYS KC_RSFT, KC_TRNS, KC_RBRC
#define LCPO_KEYS KC_LCTL, KC_TRNS, KC_MINS
#define RCPC_KEYS KC_RCTL, KC_TRNS, KC_EQL

// No need for the single versions when multi performance isn't a problem =D
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SPLASH
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH

// 20m timeout (20m * 60s * 1000mil)
// #define RGB_MATRIX_TIMEOUT 1200000
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define OLED_SCROLL_TIMEOUT 20000
#define ONESHOT_TAP_TOGGLE 2

#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 8

#define ENCODER_RESOLUTION 2
