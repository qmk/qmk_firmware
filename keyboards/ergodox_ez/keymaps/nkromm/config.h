#pragma once

// default but important
#undef TAPPING_TERM
#define TAPPING_TERM 220

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// nkrom: disabling this to allow repeating the home row mods after double tap and hold.
//        remains to be seen if I often switch from key to same key mod.
//        e.g. to type d(left shift mod) and then any capital letter on rhs.
// #define TAPPING_FORCE_HOLD

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

// mods tapped or held will always register their alpha if no other key was pressed since mod tap
// #define RETRO_TAPPING
