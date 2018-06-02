/* Copyright 2018 wanleg
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

/////////////// TAP DANCE SECTION START ///////////////
//Tap Dance Declarations (list of my tap dance configurations)
enum {
  CAD_TAP_DANCE = 0
  ,CAD_TD
};

///// TAP DANCE GENERAL SETUP SECTION START /////
///// (no need to edit this section) /////
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
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    if (state->interrupted) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else return 6; //magic number. At some point this method will expand to work for more presses
}
///// TAP DANCE GENERAL SETUP SECTION END /////

///// TAP DANCE FUNCTION SETUP START /////
void on_each_tap_fn(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
//on one tap
  case 1:
    SEND_STRING(SS_LGUI("l"));
    backlight_set(3);
	break;
//on two taps within tapping term
  case 2:
    SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_DELETE))));
    backlight_set(0);
    break;
  }
}

//what to do when dance action finishes
void on_dance_finished_fn(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    //reset_keyboard();
    reset_tap_dance(state);
  }
}

//what to do when tap dance action resets
void on_dance_reset_fn(qk_tap_dance_state_t *state, void *user_data) {
  //my use case doesn't need anything done
}
///// TAP DANCE FUNCTION SETUP END   /////
///// QUAD FUNCTION TAP DANCE PERSONALIZATION SECTION START /////
//instantialize an instance of 'tap' for the 'CAD' tap dance.
static tap CADtap_state = {
  .is_press_action = true,
  .state = 0
};

void CAD_finished (qk_tap_dance_state_t *state, void *user_data) {
  CADtap_state.state = cur_dance(state);
  switch (CADtap_state.state) {
    case SINGLE_TAP: 
		//register_code(KC_SPC); 
		SEND_STRING(SS_LGUI("l"));
		backlight_set(3);
		break;
    case SINGLE_HOLD: register_code(KC_NO); break;
    case DOUBLE_TAP: 
		//register_code(KC_ENT); 
		SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_DELETE))));
		backlight_set(0);
		break;
    case DOUBLE_HOLD: register_code(KC_NO); break; // setting double hold to do nothing (change this if you want)
    case DOUBLE_SINGLE_TAP: register_code(KC_NO); unregister_code(KC_NO); register_code(KC_NO);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void CAD_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (CADtap_state.state) {
    case SINGLE_TAP: 
		//register_code(KC_SPC); 
		SEND_STRING(SS_LGUI("l"));
		backlight_set(3);
		break;
    case SINGLE_HOLD: register_code(KC_NO); break;
    case DOUBLE_TAP: 
		//register_code(KC_ENT); 
		SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_DELETE))));
		backlight_set(0);
		break;
    case DOUBLE_HOLD: register_code(KC_NO);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_NO);
  }
  CADtap_state.state = 0;
}
///// QUAD FUNCTION TAP DANCE PERSONALIZATION SECTION END /////

//Tap Dance Definitions
//THIS SECTION HAS TO BE AT THE END OF THE TAP DANCE SECTION
qk_tap_dance_action_t tap_dance_actions[] = {
 [CAD_TAP_DANCE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME (on_each_tap_fn, on_dance_finished_fn, on_dance_reset_fn,700)
,[CAD_TD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, CAD_finished, CAD_reset)
};

//In Layer declaration, add tap dance item in place of a key code
//TD(CAD_TAP_DANCE)
///////////// TAP DANCE SECTION END ///////////////

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT( /* Base */
/*
TD(CAD_TAP_DANCE) \
*/
TD(CAD_TD) \
),
};

void led_set_user(uint8_t usb_led) {

}
