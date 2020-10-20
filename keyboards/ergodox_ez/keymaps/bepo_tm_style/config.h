#include "../../config.h"

// Sets good default for the speed of the mouse.
#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED

#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          100
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7

#undef MOUSEKEY_WHEEL_MAX_SPEED
#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#undef MOUSEKEY_WHEEL_DELAY

#define MOUSEKEY_WHEEL_MAX_SPEED    5
#define MOUSEKEY_WHEEL_TIME_TO_MAX  60
#define MOUSEKEY_WHEEL_DELAY        100

#undef TAPPING_TOGGLE
#undef TAPPING_TERM

#define TAPPING_TOGGLE  3
#define TAPPING_TERM    150

// Disable the option to have recursive macros that can block the keyboard.
#define DYNAMIC_MACRO_NO_NESTING

// NKRO is activated by default (otherwise we need a keyboard command for it).
#define FORCE_NKRO

// Disable some features that we don’t need to save space.
// Other features are enabled/disabled in rules.mk.

// These two features require CONSOLE_ENABLE = yes in rules.mk to do anything.
// #define NO_DEBUG  // The debug messages are not taking that much space, we can keep them.
#define NO_PRINT  // The info messages are using a lot of memory.
#define NO_ACTION_MACRO  // disable old-style macro.
#define NO_ACTION_FUNCTION
