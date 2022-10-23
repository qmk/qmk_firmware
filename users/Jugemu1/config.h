#pragma once

// how long before a tap becomes a hold
#undef TAPPING_TERM
#define TAPPING_TERM 200

// makes tap and hold keys work better for fast typers who don't want
// tapping term set above 500
// #define PERMISSIVE_HOLD

// tap anyway, even after TAPPING_TERM, if there was no other key
// interruption between press and release
// #define RETRO_TAPPING

#define IGNORE_MOD_TAP_INTERRUPT

// // how many taps before triggering the toggle
// #undef ONESHOT_TAP_TOGGLE
// #define ONESHOT_TAP_TOGGLE 2

// // how long before oneshot modifier key times out (currently only shift)
// #undef ONESHOT_TIMEOUT
// #define ONESHOT_TIMEOUT 2000

#define COMBO_TERM 15 // window in milliseconds to trigger combo
#define COMBO_TERM_PER_COMBO
#define COMBO_MUST_HOLD_MODS

#define EECONFIG_MODE_INDEX (uint8_t *) 19
#define EECONFIG_COMBO_INDEX (uint8_t *) 20
#define EECONFIG_TAP_HOLD_INDEX (uint8_t *) 21

#define ARROW_LAYER 3

#define TAP_HOLD_ENABLE
