/* Copyright 2017 IslandMan93
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

//**************** Definitions needed for quad function to work *********************//
enum {
  SE_TAP_DANCE = 0
};
//Enums used to clearly convey the state of the tap dance
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5 //send SINGLE_TAP twice - NOT DOUBLE_TAP
  // Add more enums here if you want for triple, quadruple, etc.
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || state->pressed==0) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap. In example below, that means to send `xx` instead of `Escape`.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else return 6; //magic number. At some point this method will expand to work for more presses
}

//**************** Definitions needed for quad function to work *********************//
// Backspace Shift TD
//instanalize an instance of 'tap' for the 'x' tap dance.
static tap se_tap_state = {
  .is_press_action = true,
  .state = 0
};

void se_finished (qk_tap_dance_state_t *state, void *user_data) {
  se_tap_state.state = cur_dance(state);
  switch (se_tap_state.state) {
    case SINGLE_TAP: register_code(KC_SPC); break;
    case SINGLE_HOLD: register_code(KC_ENT); break;
    default: register_code(KC_SPC); unregister_code(KC_SPC); register_code(KC_SPC);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void se_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (se_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SPC); break;
    case SINGLE_HOLD: unregister_code(KC_ENT); break;
    default: unregister_code(KC_SPC);
  }
  se_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [SE_TAP_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, se_finished, se_reset)
};

// KEYMAP
extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1

enum custom_keycodes {
  PAREN_MACRO = SAFE_RANGE,
  ARROW_MACRO,
  PSELF_MACRO
};

// Make layer undefined do nothing
#define _______ KC_TRNS

// Macros
#define KC_PMAC PAREN_MACRO
#define KC_AMAC ARROW_MACRO

// Holds for layer
#define KC_DEL1 LT(_LOWER, KC_DEL)
#define KC_TAB1 LT(_LOWER, KC_TAB)

// Space on tap, enter on hold.
#define KC_SPNT TD(SE_TAP_DANCE)

#define KC_BSHT SFT_T(KC_BSPC)

// Jumps the cursor a word right or left
#define KC_WRDRT LCTL(KC_RIGHT)
#define KC_WRDLT LCTL(KC_LEFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MUTE,                   KC_MPLY,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PSCR,
    KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_VOLD,                   KC_VOLU,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_CAPS,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PGDN,                   KC_PGUP,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_BSLS,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_WRDLT,                  KC_WRDRT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
    KC_LCTL, KC_LGUI, KC_APP,  KC_LALT, KC_HOME, KC_SPNT, KC_DEL1,  KC_BSHT, KC_ENT, KC_TAB1,  KC_BSHT, KC_END,  KC_DOWN, KC_UP,   KC_LEFT, KC_RIGHT
  ),

  [_LOWER] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,                    KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   _______, _______,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,                   _______, KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, _______,
    _______, _______, KC_LBRC, KC_LPRN, KC_UNDS, KC_LCBR, _______,                   _______, KC_RCBR, KC_EQL,  KC_RPRN, KC_RBRC, KC_COLN, _______,
    _______, _______, _______, KC_PMAC, KC_MINS, KC_AMAC, _______,                   _______, _______, KC_PLUS, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case PAREN_MACRO:
                SEND_STRING("()");
                return false; break;
            case ARROW_MACRO:
                SEND_STRING("->");
                return false; break;
        }
    }
    return true;
};
