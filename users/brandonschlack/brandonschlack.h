#pragma once

#include "quantum.h"

// Define layer names
#define BL 0
#define FL 1
#define ML 2

// Config
#define TAPPING_TOGGLE 2
#define PERMISSIVE_HOLD

// Macros
enum custom_keycodes {
  KC_MAKE = SAFE_RANGE,
  KEYMAP_SAFE_RANGE
};

// Useful Defines
#define FN_CAPS   LT(FL, KC_CAPS)
#define HY_CAPS   ALL_T(KC_CAPS)
// Media Mod-Tap
#define MM_LCTL   LCTL_T(KC_MRWD)
#define MM_LALT   LALT_T(KC_MPLY)
#define MM_LGUI   LGUI_T(KC_MFFD)
// MacOS
#define MC_SLPD   LCTL(LSFT(KC_POWER)) // Sleep Display
#define MC_MSSN   HYPR(KC_F3)          // Mission Control: Configure karabiner for HYPER -> fn
#define MC_LHPD   HYPR(KC_F4)          // Launchpad: Configure karabiner for HYPER -> fn
// MacOS Media Alias
#define MC_MUTE   KC__MUTE
#define MC_VOLD   KC__VOLDOWN
#define MC_VOLU   KC__VOLUP
