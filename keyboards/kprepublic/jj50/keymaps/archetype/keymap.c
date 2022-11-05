/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>
Modified 2018 Wayne Jones (WarmCatUK) <waynekjones@gmail.com>
Modified 2019 Iason Dimitrakopoulos (idimitrakopoulos) <idimitrakopoulos@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public LicensezZZ
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "rgblight.h"
#include "quantum.h"

#define _QWERTY 0
#define _COLEMAK 1
#define _FN 2
#define _FX 3

enum {
  TD_BSPC_DEL = 0,
  TD_LCTL_LBRC = 1,
  TD_LALT_RBRC = 2,
  TD_ESC_LAYER = 3,
};


void left_brackets(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      if (!state->pressed) {
        register_code16(KC_LPRN);
      } else {
        register_code(KC_LCTL);
      }
    } else if (state->count == 2) {
        register_code16(KC_LBRC);
    } else if (state->count == 3) {
        register_code16(KC_LCBR);
    }
}

void left_brackets_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_LPRN);
    } else if (state->count == 2) {
        unregister_code16(KC_LBRC);
    } else if (state->count == 3) {
        unregister_code16(KC_LCBR);
    }

    unregister_code(KC_LCTL);
}

void right_brackets(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      if (!state->pressed) {
        register_code16(KC_RPRN);
      } else {
        register_code(KC_LALT);
      }
    } else if (state->count == 2) {
        register_code16(KC_RBRC);
    } else if (state->count == 3) {
        register_code16(KC_RCBR);
    }
}

void right_brackets_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_RPRN);
    } else if (state->count == 2) {
        unregister_code16(KC_RBRC);
    } else if (state->count == 3) {
        unregister_code16(KC_RCBR);
    }

    unregister_code(KC_LALT);
}

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7,
  TRIPLE_SINGLE_TAP = 8, //send three single taps
};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }

  if (state->count == 3) {
    if (state->interrupted) return TRIPLE_SINGLE_TAP;
    else if (state->pressed) return TRIPLE_HOLD;
    else return TRIPLE_TAP;
  }
  else return 9; //magic number. At some point this method will expand to work for more presses
}

static tap tap_state = {
  .is_press_action = true,
  .state = 0
};

void layer_switcher (qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  switch (tap_state.state) {
    case SINGLE_TAP: register_code(KC_ESC); break;
    case SINGLE_HOLD: register_code(KC_ESC); break;
    case DOUBLE_TAP: register_code(KC_ESC); break;
    case DOUBLE_HOLD: layer_on(_COLEMAK); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_ESC); unregister_code(KC_ESC); register_code(KC_ESC); break;
    case TRIPLE_TAP: register_code(KC_ESC); break;
    case TRIPLE_HOLD: layer_on(_FX); break;
    case TRIPLE_SINGLE_TAP: register_code(KC_ESC); unregister_code(KC_ESC); register_code(KC_ESC); unregister_code(KC_ESC); register_code(KC_ESC); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void layer_switcher_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_ESC); break;
    case SINGLE_HOLD: unregister_code(KC_ESC); break;
    case DOUBLE_TAP: unregister_code(KC_ESC); break;
    case DOUBLE_HOLD: break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_ESC); break;
    case TRIPLE_TAP: unregister_code(KC_ESC); break;
    case TRIPLE_HOLD: break;
    case TRIPLE_SINGLE_TAP: unregister_code(KC_ESC); break;
  }
  tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  // Single tap = Backspace | Double tap = Delete
  [TD_BSPC_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, KC_DEL),
  // Single tap = ( | Double tap = [ | Triple tap = { | Single hold = KC_LCTL
  [TD_LCTL_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_brackets, left_brackets_reset),
  // Single tap = ) | Double tap = ] | Triple tap = } | Single hold = KC_LALT
  [TD_LALT_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_brackets, right_brackets_reset),
  // Layer Switcher ESC
  [TD_ESC_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layer_switcher, layer_switcher_reset),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_ESC_LAYER):
            return 100;
        default:
            return TAPPING_TERM;
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT( \

      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+.
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
        TD(TD_ESC_LAYER),     KC_1,             KC_2,             KC_3,             KC_4,             KC_5,             KC_6,             KC_7,             KC_8,             KC_9,             KC_0,             KC_BSPC,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            KC_TAB,           KC_Q,             KC_W,             KC_E,             KC_R,             KC_T,             KC_Y,             KC_U,             KC_I,             KC_O,             KC_P,             KC_BSLS,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            KC_CAPS,          KC_A,             KC_S,             KC_D,             KC_F,             KC_G,             KC_H,             KC_J,             KC_K,             KC_L,             KC_SCLN,          KC_QUOT,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            KC_LSFT,          KC_Z,             KC_X,             KC_C,             KC_V,             KC_B,             KC_N,             KC_M,             KC_DOT,           KC_SLSH,          KC_UP,          SFT_T(KC_ENT),  \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
        TD(TD_LCTL_LBRC),     KC_LGUI,      TD(TD_LALT_RBRC),     _______,          _______,        LT(_FN, KC_SPC),    _______,        LT(_FX, KC_SPC),    KC_COMM,          KC_LEFT,          KC_DOWN,          KC_RGHT       \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+'
    ),

    [_COLEMAK] = LAYOUT( \

      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+.
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          KC_F,             KC_P,             KC_G,             KC_J,             KC_L,             KC_U,             KC_Y,             KC_SCLN,          _______,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          KC_R,             KC_S,             KC_T,             KC_D,             _______,          KC_N,             KC_E,             KC_I,             KC_O,             _______,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          _______,          _______,          _______,          KC_K,             _______,          _______,          _______,          _______,          _______,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______       \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+'
    ),

    [_FN] = LAYOUT( \

      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+.
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            KC_GRV,           KC_F1,            KC_F2,            KC_F3,            KC_F4,            KC_F5,            KC_F6,            KC_F7,            KC_F8,            KC_F9,            KC_F10,           KC_DEL,       \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            KC_PSCR,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          KC_EQUAL,     \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            KC_CAPS,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          KC_MINUS,     \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          KC_PGUP,          _______,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          KC_HOME,          KC_PGDN,          KC_END        \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+'
    ),

    [_FX] = LAYOUT( \

      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+.
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          RGB_VAI,          _______,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          RGB_VAD,          _______,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          RGB_MOD,          RGB_HUI,          RGB_TOG,      \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+|
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
            _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          _______,          RGB_SAI,          RGB_HUD,          RGB_SAD       \
      //|                |                 |                 |                 |                 |                 |                 |                 |                 |                 |                 |                  |
      //,----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+'
    ),


};
