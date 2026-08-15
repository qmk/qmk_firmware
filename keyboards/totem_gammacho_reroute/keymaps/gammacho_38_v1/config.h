#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define MASTER_LEFT
// #define MASTER_RIGHT

//#define TAPPING_TERM 170
//#define TAPPING_TERM 170

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
//#define TAPPING_FORCE_HOLD

// Auto Shift
//#define NO_AUTO_SHIFT_ALPHA
//#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
//#define AUTO_SHIFT_NO_SETUP

//#undef LOCKING_SUPPORT_ENABLE
//#undef LOCKING_RESYNC_ENABLE
//#define NO_ACTION_ONESHOT

// Tapping Term
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define TAPPING_TERM_PER_KEY

// Combos Default Layer
#define COMBO_ONLY_FROM_LAYER 0

// Mouse keys
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_MAX_SPEED      2
#define MOUSEKEY_TIME_TO_MAX    5
#define MOUSEKEY_WHEEL_DELAY    0
