#pragma once

/* *** UN-COMMENT LINES BELOW, IF YOU ARE USING AN UNDERGLOW STRIP *** */
/* #undef RGBLED_NUM */
/* #define RGBLED_NUM 4 */

/* split keyboard setup */
#define USE_SERIAL              /* SERIAL or MATRIX_I2C */
#define USE_SERIAL_PD2
#define MASTER_LEFT             /* LEFT or RIGHT (or EE_HANDS) */

/* load built-in rgblight animations */
#define RGBLIGHT_ANIMATIONS

#define MOUSEKEY_DELAY             48
#define MOUSEKEY_INTERVAL          24
#define MOUSEKEY_MOVE_DELTA        3
#define MOUSEKEY_MAX_SPEED         11 /* times faster than MOVE_DELTA */
#define MOUSEKEY_TIME_TO_MAX       10

#define MOUSEKEY_WHEEL_DELTA       1
#define MOUSEKEY_WHEEL_MAX_SPEED   1 /* times faster */
#define MOUSEKEY_WHEEL_TIME_TO_MAX 1

#define TAPPING_TERM 180

/* Prefer "hold" when "down -> up -> down" (recognized immediately as "tap twice" by default) */
#define TAPPING_FORCE_HOLD

/* Prefer "hold" when "Alt Dn -> A Dn -> A Up -> Alt Up" within the TAPPING_TERM */
#define PERMISSIVE_HOLD
