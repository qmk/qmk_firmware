#pragma once

// number of taps for TT Tap-Toggle keys to toggle
#ifdef TAPPING_TOGGLE
#undef TAPPING_TOGGLE
#endif
#define TAPPING_TOGGLE 2

// time in ms that counts as a "tap" for various features
#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 100

// https://docs.qmk.fm/features/mouse-keys#configuring-the-behavior-of-mousekeys
#define MOUSEKEY_DELAY        0
#define MOUSEKEY_INTERVAL     20
#define MOUSEKEY_MAX_SPEED    10
#define MOUSEKEY_TIME_TO_MAX  15
#define MOUSEKEY_WHEEL_MAX_SPEED   1
#define MOUSEKEY_WHEEL_TIME_TO_MAX 255

// flags from user/twschum/
#define TWSCHUM_TAPPING_CTRL_PREFIX 1
