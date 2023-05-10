#pragma once

#define AUTO_SHIFT_TIMEOUT 210

#define NO_AUTO_SHIFT_NUMERIC
// #define NO_AUTO_SHIFT_SPECIAL

// retro shift is auto shift on home row mods
// If RETRO_SHIFT is defined to a value, hold times greater 
// than that value will not produce a tap on release. This enables 
// modifiers to be held for combining with mouse clicks without 
// generating taps on release.
#define RETRO_SHIFT 425

// can also be defined without a value
// #define RETRO_SHIFT

// Configure the global tapping term (default: 200ms)
// Lower than 250 and I can't tap dance brackets without a run up.
#define TAPPING_TERM 250

#define TAPPING_TERM_PER_KEY

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Apply the modifier on keys that are tapped during a short hold of a modtap
// Prevents slurred typing (of home row mods)
#define PERMISSIVE_HOLD

#define COMBO_COUNT 2

// the make command:
// From ~/qmk_firmware
// make keyboardio/atreus:slf-atreus:flash
