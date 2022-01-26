#pragma once

// default but used in macros
#undef TAPPING_TERM
#define TAPPING_TERM 180
#define TAPPING_TERM_PER_KEY

#define COMBO_COUNT 5
// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Auto Shift
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM

#define EE_HANDS

/* mouse config */
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY 0