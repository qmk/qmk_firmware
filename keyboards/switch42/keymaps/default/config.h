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

#define TAPPING_TERM 180

/* Prefer "hold" when "down -> up -> down" (recognized immediately as "tap twice" by default) */
#define TAPPING_FORCE_HOLD

/* Prefer "hold" when "Alt Dn -> A Dn -> A Up -> Alt Up" within the TAPPING_TERM */
#define PERMISSIVE_HOLD
