// Settings for home row mods
#ifdef TAPPING_TERM
    #undef TAPPING_TERM
    #define TAPPING_TERM 250
#endif
#define IGNORE_MOD_TAP_INTERRUPT

// Mouse Settings: Smoothing out mouse movement on keypress
#ifndef MOUSEKEY_INTERVAL
    #undef MOUSEKEY_INTERVAL
    #define MOUSEKEY_INTERVAL 16
#endif
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0