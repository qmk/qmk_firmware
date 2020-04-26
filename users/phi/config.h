/* ---- tapping */

#ifndef NO_ACTION_TAPPING

/* in ergo42, TAPPING_TERM is defined in rev1/config.h */
#ifdef TAPPING_TERM
#    undef TAPPING_TERM
#endif

#define TAPPING_TERM 180

/* Prefer "tap then hold" when "down -> up -> down" ("tap twice" by default) */
#define TAPPING_FORCE_HOLD

/* Prefer "hold" when "Alt Dn -> A Dn -> A Up -> Alt Up" within the TAPPING_TERM */
#define PERMISSIVE_HOLD

#endif

/* ---- mousekey */

#ifdef MOUSEKEY_ENABLE

#define MOUSEKEY_DELAY             48
#define MOUSEKEY_INTERVAL          24
#define MOUSEKEY_MOVE_DELTA        3
#define MOUSEKEY_MAX_SPEED         15 /* times faster than MOVE_DELTA */
#define MOUSEKEY_TIME_TO_MAX       17

#define MOUSEKEY_WHEEL_DELAY       72
#define MOUSEKEY_WHEEL_INTERVAL    72
#define MOUSEKEY_WHEEL_DELTA       1
#define MOUSEKEY_WHEEL_MAX_SPEED   4 /* times faster */
#define MOUSEKEY_WHEEL_TIME_TO_MAX 255 /* disable auto-accel */

#endif

/* ---- rgblight */

#ifdef RGBLIGHT_ENABLE

#define RGBLIGHT_HUE_STEP 2
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#endif

/* ---- rgb matrix */

#ifdef RGB_MATRIX_ENABLE

#define RGB_MATRIX_HUE_STEP 2
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8

#endif
