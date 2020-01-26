#pragma once

// place overrides here

#define PERMISSIVE_HOLD

#define RGBLIGHT_EFFECT_BREATHING


/* Some defines meant to decrease the firmware size.
 */
//Disable old style macro handling: MACRO() & action_get_macro
#define NO_ACTION_MACRO // This saves 320 bytes
//disable calling of action_function() from the fn_actions array (deprecated)
#define NO_ACTION_FUNCTION  // This saves 96 bytes
    //#define LINK_TIME_OPTIMIZATION_ENABLE // Did not decrease firmware size when tested on 26 Jan 2020 
    //#define NO_DEBUG //disable debugging (already defined)
    //#define NO_PRINT JJdisable printing/debugging using hid_listen (already defined)
    //#define NO_ACTION_LAYER //disable layers (obviously need layers)
    //#define NO_ACTION_TAPPING // This saves 2516 bytes (9%) (keymap uses tapping)
    //#define NO_ACTION_ONESHOT // This did not reduse firmware size on 26 Jan 2020

