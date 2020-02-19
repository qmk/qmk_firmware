/* Copyright 2020 Swiftrax
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
#define FN MO(2)
#define SWAPQ TO(0)
#define SWAPD TO(1)

static const char * const ANSWERS[] = {
"You know what they say, dogs can't swim with lead shoes\n",
"You can butter up a cat and throw it in the oven. Just don't call it biscuits.\n",
"It smells like up dog in here.\n",
"I disagree.\n",
"It really be like that sometimes.\n"
};

#define NUM_ANSWERS 5 

enum custom_keycodes{
	TASK = SAFE_RANGE,
	WIND,
	WINL,
	RAGE,
	RAND
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
	  case TASK:
      if (record->event.pressed) { //open task manager
        // when keycode TASK is pressed
        register_code(KC_LSFT);
		register_code(KC_LCTL);
		register_code(KC_ESC);
      } else {
        // when keycode TASK is released
		unregister_code(KC_LSFT);
		unregister_code(KC_LCTL);
		unregister_code(KC_ESC);
      }
      break;
    case WIND:
      if (record->event.pressed) { //go to desktop
        // when keycode WIND is pressed
        register_code(KC_LGUI);
		tap_code(KC_D);
      } else {
        // when keycode WIND is released
		unregister_code(KC_LGUI);
      }
      break;
    case WINL:
      if (record->event.pressed) { //lock computer
        // when keycode WINL is pressed
        register_code(KC_LGUI);
		tap_code(KC_L);
      } else {
        // when keycode WINL is released
		unregister_code(KC_LGUI);
      }
      break;
	case RAGE:
      if (record->event.pressed) { //ALT + F4
        // when keycode RAGE is pressed
        register_code(KC_LALT);
		tap_code(KC_F4);
      } else {
        // when keycode RAGE is released
		unregister_code(KC_LALT);
      }
      break;
	 case RAND:
      if (record->event.pressed) { //RAND String
        // when keycode RAND is pressed
        uint8_t num = rand() / (RAND_MAX / NUM_ANSWERS + 1);
		send_string(ANSWERS[num]);
      } else {
        // when keycode RAND is released
      }
	  break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT( /*base layer*/
		RAGE, RAND, KC_ESC, 	KC_1, 	KC_2, 	KC_3, 	KC_4, 	KC_5, 	KC_6, 	KC_7, 	KC_8, 	KC_9, 	KC_0, 	 KC_MINS, 	KC_EQL, KC_GRV, KC_BSLS, 
		TASK, SWAPD, KC_TAB, 	KC_Q, 	KC_W, 	KC_E, 	KC_R, 	KC_T, 	KC_Y, 	KC_U, 	KC_I, 	KC_O, 	KC_P, 	 KC_LBRC, 	KC_RBRC,KC_BSPC,KC_DEL, 
		WIND, KC_F15, KC_LCTL, KC_A, 	KC_S, 	KC_D, 	KC_F, 	KC_G, 	KC_H, 	KC_J, 	KC_K, 	KC_L, 	KC_SCLN, KC_QUOT, 	KC_ENT, KC_MUTE, KC_PGUP, 
		WINL, KC_F16, KC_LSFT, KC_Z, 	KC_X, 	KC_C, 	KC_V, 	KC_B, 	KC_N, 	KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_RSFT, 	KC_UP, 			KC_PGDN, 
		KC_LGUI, KC_F17, KC_LCTL, KC_LALT, 				KC_SPC, 			KC_RALT, 	FN, 				   	  KC_LEFT, KC_DOWN, KC_RGHT), 
		
	[1] = LAYOUT( /*dvorak*/
		RAGE, RAND, KC_ESC, 	KC_1, 	KC_2, 	KC_3, 	KC_4, 	KC_5, 	KC_6, 	KC_7, 	KC_8, 	KC_9, 	KC_0, 	 KC_RBRC, 	KC_LBRC, KC_GRV, KC_BSLS, 
		TASK, SWAPQ, KC_TAB, 	KC_QUOT, 	KC_COMM, 	KC_DOT, 	KC_P, 	KC_Y, 	KC_F, 	KC_G, 	KC_C, 	KC_R, 	KC_L, 	 KC_SLSH, 	KC_EQL,KC_BSPC,KC_DEL, 
		WIND, KC_F15, KC_LCTL, KC_A, 	KC_O, 	KC_E, 	KC_U, 	KC_I, 	KC_D, 	KC_H, 	KC_T, 	KC_N, 	KC_S, KC_MINS, 	KC_ENT, KC_MUTE, KC_PGUP, 
		WINL, KC_F16, KC_LSFT, KC_SCLN, 	KC_Q, 	KC_J, 	KC_K, 	KC_X, 	KC_B, 	KC_M,   KC_W,	KC_V, KC_Z, KC_RSFT, 	KC_UP, 			KC_PGDN, 
		KC_LGUI, KC_F17, KC_LCTL, KC_LALT, 				KC_SPC, 			KC_RALT, 	FN, 				   	  KC_LEFT, KC_DOWN, KC_RGHT), 
	
	[2] = LAYOUT( /*fn layer*/
		_______, _______, _______, 	KC_F1, 	KC_F2, 	KC_F3, 	KC_F4, 	KC_F5, 	KC_F6, 	KC_F7, 	KC_F8, 	KC_F9, 	KC_F10, 	 KC_F11, 	KC_F12, _______, _______, 
		_______, _______, _______, 	_______, 	_______, 	_______, 	_______, 	_______, 	_______, 	_______, 	_______, 	_______, 	_______, 	 _______, 	_______,_______,_______, 
		_______, _______, KC_CAPS, _______, 	_______, 	_______, 	_______, 	_______, 	_______, 	_______, 	_______, 	_______, 	_______, _______, 	_______, _______, _______, 
		_______, _______, _______, _______, 	_______, 	_______, 	_______, 	_______, 	_______, 	_______,   _______,_______, _______, _______, 	_______, 			_______, 
		_______, KC_PSCR, _______, _______, 				_______, 			_______, 	_______, 				   _______, _______, _______
	),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
