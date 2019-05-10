#pragma once

#include "quantum.h"

// Define layer names
enum layer_names {
    LB_MAC = 0,
    LF_MAC,
    LB_WIN,
    LF_WIN,
    LB_NIX,
    LF_NIX,
    LK_MGC,
};

// Config
#define TAPPING_TOGGLE 2
#define PERMISSIVE_HOLD

// Macros
enum custom_keycodes {
  KC_MAKE = SAFE_RANGE,
  MD_MAKE,
  OS_MAC,
  OS_WIN,
  OS_NIX,
  WN_SLPD,
  KEYMAP_SAFE_RANGE
};

// Useful Defines
#define HY_CAPS   ALL_T(KC_CAPS)
#define TG_MAGC   TG(LK_MGC)
// Media Mod-Tap
#define MM_LCTL   LCTL_T(KC_MRWD)
#define MM_LALT   LALT_T(KC_MPLY)
#define MM_LGUI   LGUI_T(KC_MFFD)
#define MM_FN_M   LT(LF_MAC, KC_MPLY)
#define MM_FN_W   LT(LF_WIN, KC_MPLY)
#define MM_FN_X   LT(LF_NIX, KC_MPLY)
#define MM_RSFT   RSFT_T(KC_MUTE)
// MacOS
#define MC_POWR   KC_POWER             // Mac Power alias
#define MC_SLPD   LCTL(LSFT(KC_POWER)) // Sleep Display
#define MC_MSSN   LCTL(KC_UP)          // Mission Control
#define MC_LHPD   KC_F13               // Launchpad: Configure karabiner for F13 -> Launchpad
#define MC_PLYR   LGUI(KC_F8)          // Focuses current Media Player
// Windows
#define WN_LOCK   LGUI(KC_L)           // Lock Computer
#define WN_TSKM   LCTL(LALT(KC_DEL))   // Task Manager (Ctrl+Alt+Del)
