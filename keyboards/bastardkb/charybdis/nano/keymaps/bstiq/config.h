#pragma once

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD
    
// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD

// custom layer names and redo/undo copied over from miryoku
#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used
#define U_RDO KC_AGIN
#define U_PST S(KC_INS)
#define U_CPY C(KC_INS)
#define U_CUT S(KC_DEL)
#define U_UND KC_UNDO

#define CHARYBDIS_DRAGSCROLL_MOMENTARY
#define CHARYBDIS_DRAGSCROLL_FIXED

/* Default miryoku layers */
#define BASE  0
#define MBO   1
#define MEDIA 2
#define NAV   3
#define MOUSE 4
#define SYM   5
#define NUM   6
#define FUN   7