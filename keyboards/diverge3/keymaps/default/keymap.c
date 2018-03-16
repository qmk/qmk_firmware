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
#include "diverge3.h"
#include "action_layer.h"
#include "eeconfig.h"

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
#define KC_ KC_TRNS

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

  [_QWERTY] = KC_KEYMAP(
  //,----+----+----+----+----+----+----|           |----+----+----+----+----+----+----|
      ESC, 1  , 2  , 3  , 4  , 5  ,MUTE,            MPLY, 6  , 7  , 8  , 9  , 0  ,PSCR,
  //|----+----+----+----+----+----+----|           |----+----+----+----+----+----+----|
      GRV, Q  , W  , E  , R  , T  ,VOLD,            VOLU, Y  , U  , I  , O  , P  ,CAPS,
  //|----+----+----+----+----+----+----|           |----+----+----+----+----+----+----|
      TAB, A  , S  , D  , F  , G  ,PGDN,            PGUP, H  , J  , K  , L  ,SCLN,BSLS,
  //|----+----+----+----+----+----+----|           |----+----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,WRDLT,          WRDRT, N  , M  ,COMM,DOT ,SLSH,QUOT,
  //|----+----+----+----+----+----+----+----|||----+----+----+----+----+----+----+----|
     LCTL,LGUI, APP,LALT,HOME,SPNT,DEL1,BSHT , ENT ,TAB1,BSHT,END ,DOWN, UP ,LEFT,RIGHT
  ),

  [_LOWER] = KC_KEYMAP(
  //,----+----+----+----+----+----+----|           |----+----+----+----+----+----+----|
         , F1 , F2 , F3 , F4 , F5 ,F11 ,             F12, F6 , F7 , F8 , F9 ,    ,    ,
  //|----+----+----+----+----+----+----|           |----+----+----+----+----+----+----|
     TILD,EXLM, AT ,HASH,DLR ,PERC,    ,                ,CIRC,AMPR,ASTR,    ,    ,    ,
  //|----+----+----+----+----+----+----|           |----+----+----+----+----+----+----|
         ,    ,LBRC,LPRN,UNDS,LCBR,    ,                ,RCBR, EQL,RPRN,RBRC,COLN,    ,
  //|----+----+----+----+----+----+----|           |----+----+----+----+----+----+----|
         ,    ,    ,PMAC,MINS,AMAC,    ,                ,    ,PLUS,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----+----|||----+----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,     ,     ,    ,    ,    ,    ,    ,    ,
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
