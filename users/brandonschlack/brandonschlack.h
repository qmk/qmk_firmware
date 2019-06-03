#pragma once

#include "quantum.h"
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   include "rgb_bs.h"
#endif

// Define layer names
enum bs_layers {
    _MAC = 0,
    _MACFN,
    _WIN,
    _WINFN,
    _MAGIC = 15,
};

// Config
#define TAPPING_TOGGLE 2
#define PERMISSIVE_HOLD

// Macros
enum custom_keycodes {
  KC_MAKE = SAFE_RANGE,
  KC_FLSH,
  MD_MAKE,
  OS_MAC,
  OS_WIN,
  CMD_TAB,
  WN_SLPD,
  KEYMAP_SAFE_RANGE
};

// Useful Defines
#define HY_CAPS   ALL_T(KC_CAPS)
#define TG_MAGC   TG(_MAGIC)
// Media Mod-Tap
#define MM_LCTL   LCTL_T(KC_MRWD)
#define MM_LALT   LALT_T(KC_MPLY)
#define MM_LGUI   LGUI_T(KC_MFFD)
#define MM_FN_M   LT(_MACFN, KC_MPLY)
#define MM_FN_W   LT(_WINFN, KC_MPLY)
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
