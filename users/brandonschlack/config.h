#pragma once

#define TAPPING_TOGGLE 2
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define TAP_HOLD_CAPS_DELAY 200
#define GRAVE_ESC_ALT_OVERRIDE

#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_SLEEP
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   define RGB_THEME_ENABLE
#endif

#ifdef RGB_THEME_ENABLE
#   define DISABLE_RGB_THEME_STRIKER
#   define DISABLE_RGB_THEME_OBLIQUE
#endif

#ifdef ENCODER_ENABLE
#    define TAP_CODE_DELAY 10
#else
#    define TAP_CODE_DELAY 5
#endif

/* Disable unused and unneeded features to reduce on firmware size */
#ifndef NO_ACTION_MACRO
#   define NO_ACTION_MACRO
#endif
#ifndef NO_ACTION_FUNCTION
#   define NO_ACTION_FUNCTION
#endif

#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif
