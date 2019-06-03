#pragma once


////////////////////////////////////////////////////////////////////////////////
// Features That Can Be Enabled
// https://docs.qmk.fm/reference/config-options#features-that-can-be-enabled
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Behaviors That Can Be Configured
// https://docs.qmk.fm/reference/config-options#behaviors-that-can-be-configured
////////////////////////////////////////////////////////////////////////////////

// MS the button needs to be held before a tap becomes a hold (default: 200)
#undef TAPPING_TERM
#define TAPPING_TERM    250

// Makes it easier for fast typists to use dual-role keys. See additional details here:
// https://docs.qmk.fm/features/advanced-keycodes#permissive-hold
#define PERMISSIVE_HOLD

// MS after tapping the Leader key to listen for a sequence (default: 300)
#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT  750

// This makes it possible to do rolling combos (zx) with keys that convert to other keys on hold
// (for example, if z becomes ctrl when you hold it, when this option isn't enabled, z rapidly
// followed by x actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT



////////////////////////////////////////////////////////////////////////////////
// Mouse Key Options
// https://docs.qmk.fm/reference/config-options#mouse-key-options
////////////////////////////////////////////////////////////////////////////////

#ifdef MOUSEKEY_ENABLE
// Mouse key config

// Frequency with which cursor movements are sent. Lower means more resolution / DPI.
// Default: 20
// #undef MOUSEKEY_INTERVAL
// #define MOUSEKEY_INTERVAL       20

// MS after pressing the key before initial movement begins. Lower means quicker response.
// Default: 0
// #undef MOUSEKEY_DELAY
// #define MOUSEKEY_DELAY          0

// MS it takes the cursor to accelerate to max speed
// Default: 60
// #undef MOUSEKEY_TIME_TO_MAX
// #define MOUSEKEY_TIME_TO_MAX    60

// Maximum speed for the mouse keys
// Default: 7
// #undef MOUSEKEY_MAX_SPEED
// #define MOUSEKEY_MAX_SPEED      7

// Delay before the mouse wheel
// Default: 0
// #undef MOUSEKEY_WHEEL_DELAY
// #define MOUSEKEY_WHEEL_DELAY    0

#endif // MOUSEKEY_ENABLE
