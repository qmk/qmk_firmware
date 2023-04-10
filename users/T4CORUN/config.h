#pragma once

/* This file is designed to have settings that apply to all my keyboards */

/* Clear out variables that we may be setting */
#ifdef USB_POLLING_INTERVAL_MS
# undef USB_POLLING_INTERVAL_MS
#endif

#ifdef TAPPING_TERM
# undef TAPPING_TERM
#endif

/* Common configuration across all keyboards */
#define USB_POLLING_INTERVAL_MS 1

#define HOLD_ON_OTHER_KEY_PRESS

#define QUICK_TAP_TERM 120
#define QUICK_TAP_TERM_PER_KEY

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

#ifdef MOUSEKEY_ENABLE
# define MOUSEKEY_INTERVAL 12
# define MOUSEKEY_MAX_SPEED 6
# define MOUSEKEY_TIME_TO_MAX 50
# define MOUSEKEY_DELAY 20
#else
# undef MOUSEKEY_INTERVAL
# undef MOUSEKEY_MAX_SPEED
# undef MOUSEKEY_TIME_TO_MAX
# undef MOUSEKEY_DELAY
#endif //MOUSEKEY_ENABLE

#ifdef ONESHOTKEY_ENABLE
# define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped once again. */
# define ONESHOT_TIMEOUT 3000  /* Time (in ms) before the one shot key is released */
#else
# undef ONESHOT_TAP_TOGGLE
# undef ONESHOT_TIMEOUT
# define NO_ACTION_ONESHOT    /* So far I only use one shot mods on 3x5 keyboards. Adding this will save space */
#endif //ONESHOTKEY_ENABLE

#ifdef LEADER_ENABLE
# define LEADER_TIMEOUT 1000 /* I am not sure if I have any boards that use this */
#else
# undef LEADER_TIMEOUT
#endif //LEADER_ENABLE

#ifdef COMBO_ENABLE
# define COMBO_VARIABLE_LEN
# define COMBO_TERM 50
#else
# undef COMBO_VARIABLE_LEN
# undef COMBO_TERM
#endif //COMBO_ENABLE
