#pragma once
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT
#define RGBLIGHT_SLEEP



/* Leader Key
   ========================================================================== */

// Activates the leader key
// #define LEADER_PER_KEY_TIMING
// resets the timeout after each key is tapped
// #define LEADER_TIMEOUT 240






/* Autoshifting
   ========================================================================== */

// This controls how long you have to hold a key before you get the shifted state.
#define AUTO_SHIFT_TIMEOUT 150

// Do not Auto Shift special keys -_, =+, [{, ]}, ;:, '", ,<, .>, and /?
// #define NO_AUTO_SHIFT_SPECIAL

// Do not Auto Shift numeric keys, zero through nine.
#define NO_AUTO_SHIFT_NUMERIC

// Do not Auto Shift alpha characters, which include A through Z.
// #define NO_AUTO_SHIFT_ALPHA

// Lower the Auto Shift timeout variable (down)
// KC_ASDN

// Raise the Auto Shift timeout variable (up)
// KC_ASUP

// Report your current Auto Shift timeout value
// KC_ASRP

// Turns on the Auto Shift Function
// KC_ASON

// Turns off the Auto Shift Function
// KC_ASOFF

// Toggles the state of the Auto Shift feature
// KC_ASTG
