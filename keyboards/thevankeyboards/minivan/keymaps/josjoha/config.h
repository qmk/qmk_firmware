#pragma once


// place overrides here

/* Some defines meant to decrease the firmware size.
 */
#ifndef LINK_TIME_OPTIMIZATION_ENABLE
    //Disable old style macro handling: MACRO() & action_get_macro
    #define NO_ACTION_MACRO // This saves 320 bytes
    //disable calling of action_function() from the fn_actions array (deprecated)
    #define NO_ACTION_FUNCTION  // This saves 96 bytes
#endif

#define PERMISSIVE_HOLD
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_SLEEP // QMK docs: "If defined, the RGB lighting will be switched off when the host goes to sleep"

// Layer switch TT(layer) tapping amount to make it toggle
#define TAPPING_TERM_HOLTAP 225 // 175 ms proved unreliable, 225 ms seems ok (personal preference)


// Attempts to reduce firmware size:
    //#define LINK_TIME_OPTIMIZATION_ENABLE // Did not decrease firmware size when tested on 26 Jan 2020 
    //#define NO_DEBUG //disable debugging (already defined)
    //#define NO_PRINT JJdisable printing/debugging using hid_listen (already defined)
    //#define NO_ACTION_LAYER //disable layers (obviously need layers)
    //#define NO_ACTION_TAPPING // This saves 2516 bytes (9%) (keymap uses tapping)
    //#define NO_ACTION_ONESHOT // This did not reduse firmware size on 26 Jan 2020

