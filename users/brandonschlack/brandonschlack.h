#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// Define layer names
#define BASE  0
#define FUNCT 1

// Config
#define TAPPING_TOGGLE 2
#define PERMISSIVE_HOLD

// Macros
enum custom_keycodes {
  KC_LHPD = SAFE_RANGE,
  KEYMAP_SAFE_RANGE
};

// Useful Defines
#define FN_CAPS   LT(FUNCT, KC_CAPS)
#define HY_CAPS   ALL_T(KC_CAPS)
// MacOS
#define MC_SLPD   LCTL(LSFT(KC_POWER)) // Sleep Display
#define MC_MSSN   HYPR(KC_F3)          // Mission Control: Configure karabiner for HYPER -> fn
#define MC_LHPD   HYPR(KC_F4)          // Launchpad: Configure karabiner for HYPER -> fn
// MacOS Media Alias
#define MC_MUTE   KC__MUTE
#define MC_VOLD   KC__VOLDOWN
#define MC_VOLU   KC__VOLUP

#endif
