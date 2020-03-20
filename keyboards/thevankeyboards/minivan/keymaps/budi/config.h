#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// place overrides here
#ifdef DEBOUNCE
#undef DEBOUNCE
#endif
#define DEBOUNCE 2
#define MOUSEKEY_INTERVAL           10
#define MOUSEKEY_DELAY              0
#define MOUSEKEY_TIME_TO_MAX        120
#define MOUSEKEY_MAX_SPEED          9
#define MOUSEKEY_WHEEL_DELAY        0
#define MOUSEKEY_WHEEL_MAX_SPEED    2
#define MOUSEKEY_WHEEL_TIME_TO_MAX  120
#define TAPPING_TOGGLE         1
#define TAPPING_TERM           200
#define IGNORE_MOD_TAP_INTERRUPT
#define FORCE_NKRO
#endif
