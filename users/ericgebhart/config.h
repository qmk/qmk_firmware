#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H

#include "../../config.h"

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define COMBO_MUST_HOLD_MODS
#define COMBO_HOLD_TERM 150
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
#undef IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_TOGGLE  2
#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT

#endif
