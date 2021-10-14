#pragma once

#include "quantum.h"

#define SYMB_BSPC LT(_SYMBOL, KC_BSPACE)
#define NAV_SPC LT(_NAVIGATION, KC_SPACE)
#define UNIQ(X) RALT(RCTL(RGUI(RSFT(X))))
#define MY_A CTL_T(KC_A)
#define MY_R SFT_T(KC_R)
#define MY_S ALT_T(KC_S)
#define MY_Z GUI_T(KC_Z)
#define MY_SLASH GUI_T(KC_SLASH)
#define MY_E ALT_T(KC_E)
#define MY_I SFT_T(KC_I)
#define MY_O CTL_T(KC_O)

enum layers {
  _COLEMAK = 0,
  _SYMBOL,
  _NAVIGATION,
  _ADJUST
};

enum keycodes {
  VIM_SAVE = SAFE_RANGE + 1024,
  VIM_QUIT,
  VIM_WRITE,
};

layer_state_t layer_state_set_user(layer_state_t state);
