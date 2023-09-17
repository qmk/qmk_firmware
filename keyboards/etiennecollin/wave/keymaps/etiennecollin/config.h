#pragma once

// Activate caps word by pressing Left Shift + Right Shift
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat
#define QUICK_TAP_TERM 0

// Maximum time between taps of tap dances
#define TAPPING_TERM 175

// Perform hold action if pressing a dual-role key, tapping another key and
// releasing the dual-role key withing tapping term
#define PERMISSIVE_HOLD

// Perform hold action if pressing a dual-role key, pressing another key,
// releasing the dual-role key and releasing the other key withing tapping term
#define HOLD_ON_OTHER_KEY_PRESS

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64

// Thumb Combos
#define COMBO_COUNT 2
#define COMBO_TERM 200
#define EXTRA_SHORT_COMBOS
