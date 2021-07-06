#pragma once

#ifdef OLED_DRIVER_ENABLE
#  define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
// #    define RGBLIGHT_ANIMATIONS
#  define RGBLIGHT_HUE_STEP 8
#  define RGBLIGHT_SAT_STEP 16
#  define RGBLIGHT_VAL_STEP 16
#  define RGBLIGHT_LIMIT_VAL 150
#  define RGBLIGHT_SLEEP
// #    define RGBLIGHT_LAYERS
#endif

#ifdef TAP_DANCE_ENABLE
// Change "hold" time (default is 200 ms)
// -- used for tap dance and other tap mods
#  define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods.
#  define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#  define TAPPING_FORCE_HOLD

#endif

// Reduce firmware size
// 	https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
// also requires EXTRAFLAGS in config.h
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
