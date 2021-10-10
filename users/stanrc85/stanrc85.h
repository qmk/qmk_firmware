#pragma once

#include "quantum.h"
#include "version.h"

enum my_layers {
  _NUMPAD = 0,  //Macropad numpad
  _NAVKEY,      //Macropad nav keys
  _MEDIA,       //Macropad media controls
  _RGB,         //Macropad RGB controls
  _FN1PAD,      //Macropad reset and make commands
  _QWERTY = 0,  //Qwerty with custom shortcuts and functions
  _DEFAULT,     //Default ANSI for gaming, enable with FN2+RCtl
  _FN1_60,      //Function keys, arrows, custom shortcuts, volume control
  _FN2_60       //RGB Underglow controls and RESET
};

//Aliases for longer keycodes
#define KC_CAD	LALT(LCTL(KC_DEL))
#define KC_LOCK	LGUI(KC_L)
#define CA_QUOT LCA(KC_QUOT)
#define CA_SCLN LCA(KC_SCLN)
#define KC_CTLE LCTL_T(KC_ESC)
#define LT_SPCF LT(_FN1_60, KC_SPC)
#define LT_BPCF LT(_FN1_60, KC_BSPC)
#define TD_TESC TD(TD_ESC)
#define TD_TWIN TD(TD_WIN)
#define TD_TCTL TD(TD_RCTL)
#define CA_COPY LCTL(KC_C)
#define CA_PSTE LCTL(KC_V)

enum cust_keys {
  KC_MAKE = SAFE_RANGE,
  KC_RDP
};

enum tap_dance {
  TD_WIN,
  TD_ESC,
  TD_RCTL
};

// define a type containing as many tapdance states as you need
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_TAP
} td_state_t;

// function to determine the current tapdance state
int cur_dance (qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void ctl_copy_finished (qk_tap_dance_state_t *state, void *user_data);
void ctl_copy_reset (qk_tap_dance_state_t *state, void *user_data);
