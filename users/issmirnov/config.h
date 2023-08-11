#pragma once

// how long before a tap becomes a hold
#undef TAPPING_TERM
#define TAPPING_TERM 100

// makes tap and hold keys work better for fast typers who don't want
// tapping term set above 500
#define PERMISSIVE_HOLD

// tap anyway, even after TAPPING_TERM, if there was no other key
// interruption between press and release
#define RETRO_TAPPING

// how many taps before triggering the toggle
#undef ONESHOT_TAP_TOGGLE
#define ONESHOT_TAP_TOGGLE 2

// how long before oneshot modifier key times out (currently only shift)
#undef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 2000

// Enable combos for vim
#define COMBO_TERM 50 // window in milliseconds to trigger combo

// Allow more than 4 keys to be sent to the system. Useful for gaming.
// #define FORCE_NKRO

// Save 200 bytes on unused keycodes
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

// Enable HID_listen commands.
#define NO_DEBUG
#undef NO_PRINT
#define USER_PRINT

// Note: Defining the following does not have any impact on space:
// - NO_ACTION_MACRO
// - NO_ACTION_FUNCTION
// - DISABLE_LEADER
