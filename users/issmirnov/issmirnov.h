#pragma once

#include QMK_KEYBOARD_H

#include "rows.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers
enum {
  _QWERTY = 0,
  _SYMB,
  _NUMP,
  _OVERWATCH,
  _NAVI
};

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  TAP_TOG_LAYER,
  CLEAR_EEPROM,
  WKSP_LEFT, // Smart key that only activates when we are momentarily in a layer
  WKSP_RIGHT, // Smart key that only activates when we are momentarily in a layer
};


#define LOWER MO(_SYMB)
#define RAISE MO(_NUMP)

#define CTL_SPC MT(MOD_LCTL, KC_SPC)
#define OSMSFT OSM(MOD_LSFT)
#define LOCK LGUI(KC_L)
#define MODSFT LSFT(KC_LGUI)
#define APPS LGUI(KC_SPC)
