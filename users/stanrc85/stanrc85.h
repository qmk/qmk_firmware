#pragma once

#include "quantum.h"
#include "version.h"

#define DEFAULT 0  //Custom ANSI
#define LAYER1 1   //Default ANSI (enable with Fn2+CAPS)
#define LAYER2 2   //Function keys, arrows, custom shortcuts, volume control
#define LAYER3 3   //RGB Underglow controls and RESET

//Aliases for longer keycodes
#define KC_CAD	LALT(LCTL(KC_DEL))
#define KC_LOCK	LGUI(KC_L)
#define CA_QUOT LCA(KC_QUOT)
#define CA_SCLN LCA(KC_SCLN)
#define KC_CTLE LCTL_T(KC_ESC)
#define LT_SPCF LT(2, KC_SPC)
#define TD_TESC TD(TD_ESC)
#define TD_TWIN TD(TD_WIN)
#define TD_TCTL TD(TD_RCTL)

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
