/* Copyright 2020 Reid Sox-Harris
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _MACRO,
    _MOD
};

enum custom_keycodes {
    M801 = SAFE_RANGE,
    M802,
    M803,
    M804,
    M805,
    M806,
};

// tapdance keycodes
enum td_keycodes {
    LAY
};

// define a type containing as many tapdance states as you need
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
} td_state_t;

// create a global instance of the tapdance state type
static td_state_t td_state;

// declare your tapdance functions:

// function to determine the current tapdance state
int cur_dance (qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void altlp_finished (qk_tap_dance_state_t *state, void *user_data);
void altlp_reset (qk_tap_dance_state_t *state, void *user_data);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case M801:
      if (record->event.pressed) {
        SEND_STRING("M801" SS_TAP(X_ENTER));
      }
      break;
    case M802:
      if (record->event.pressed) {
          SEND_STRING("M802" SS_TAP(X_ENTER));
      }
      break;
    case M803:
      if (record->event.pressed) {
          SEND_STRING("M803" SS_TAP(X_ENTER));
      }
      break;
     case M804:
      if (record->event.pressed) {
          SEND_STRING("M804" SS_TAP(X_ENTER));
      }
      break;
    case M805:
      if (record->event.pressed) {
          SEND_STRING("M805" SS_TAP(X_ENTER));
      }
      break;
    case M806:
      if (record->event.pressed) {
          SEND_STRING("M806" SS_TAP(X_ENTER));
      }
      break;
  }

  return true;
};

#define EX_ARR LCTL(LSFT(KC_ENTER))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    // ┌────────┬────────┬────────┐
         KC_MUTE, KC_UP,  TD(LAY),
    // ├────────┼────────┼────────┤
         KC_LEFT, KC_DOWN, KC_RGHT,
    // ├────────┼────────┼────────┤
         KC_MRWD, KC_MPLY, KC_MFFD
    // └────────┴────────┴────────┘
        ),
    [_MACRO] = LAYOUT(
    // ┌────────┬────────┬────────┐
        _______,  KC_SPC, TG(_MACRO),
    // ├────────┼────────┼────────┤
          M801,    M802,    M803,
    // ├────────┼────────┼────────┤
          KC_NO,  KC_NO,   EX_ARR
    // └────────┴────────┴────────┘
        ),
    [_MOD] = LAYOUT(
    // ┌────────┬────────┬────────┐
        _______,  BL_STEP,TG(_MOD),
    // ├────────┼────────┼────────┤
        RGB_TOG, RGB_HUI, RGB_SAI,
    // ├────────┼────────┼────────┤
        RGB_MOD, RGB_HUD, RGB_SAD
    // └────────┴────────┴────────┘
        )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
}

// Tapdance! Hold to use as a modifier to the _MOD layout, tap to change it between _BASE and _MACRO

// determine the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  } else { return 3; } // any number higher than the maximum state value you return above
}

// handle the possible states for each tapdance keycode you define:

void altlp_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      layer_on(_MACRO);
      break;
    case SINGLE_HOLD:
      layer_on(_MOD);
      break;
  }
}

void altlp_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      break;
    case SINGLE_HOLD:
      layer_off(_MOD);
      break;
  }
}

// define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
  [LAY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altlp_finished, altlp_reset)
};
