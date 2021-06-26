#pragma once

/*** OLED ***/

#ifdef OLED_DRIVER_ENABLE
#    define OLED_DISPLAY_128X64
#endif

/*** RGB LIGHTS ***/

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 150

#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#    define RGBLIGHT_DEFAULT_HUE 70   // 0-255
#    define RGBLIGHT_DEFAULT_SAT 255  // 0-255
#    define RGBLIGHT_DEFAULT_VAL 150  // 0-255

#    define RGBLIGHT_SLEEP
// #    define RGBLIGHT_ANIMATIONS    // animations disabled
#endif

/*** CONTROLLERS ***/

// see https://docs.qmk.fm/#/feature_split_keyboard?id=hardware-configuration-options
// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
#define SPLIT_USB_DETECT
#define NO_USB_STARTUP_CHECK

/*** MOD_TAP ***/
/*
great guide on this topic https://precondition.github.io/home-row-mods
*/

/*
the minimum time you have to hold a key to activate the "hold" key
- used for modifiers and layer taps
- default 200
*/
#define TAPPING_TERM 400

/*
do not activate the modifier when another key is being pressed and released while the tap_key is being held before tapping_term has been reached
- prevent accidental mod usage
*/
#define IGNORE_MOD_TAP_INTERRUPT

/*
allow for hold-mod after tapping the same key for the letter itself
- disables double-tap-auto-repeat = to repeat a letter, you have to spam it instead of holding it down ..
- applies to modifier and layer taps

*/
#define TAPPING_FORCE_HOLD

/*
allow for mod-key activation, if any other key is pressed and released while the mod key is being hold
mod will then be activated even before the tapping_term has passed
- works even when IGNORE_MOD_TAP_INTERRUPT is defined
- might be useful for long tapping_term times and fast typing
- BUT might also lead to accidental mod activations (e.g. for very short, quick words)
- alternatively: see PERMISSIVE_HOLD_PER_KEY https://docs.qmk.fm/#/tap_hold?id=permissive-hold
*/
// #define PERMISSIVE_HOLD
