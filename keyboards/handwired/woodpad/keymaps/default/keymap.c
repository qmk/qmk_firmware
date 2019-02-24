/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#include "woodpad.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NUMLOCK 0
#define _NAV 1
#define _ALT 2
#define _ADJUST 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_NUMLOCK] = KEYMAP( /* Base */
  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,\
    KC_P7,  KC_P8, KC_P9, KC_PPLS,   \
    KC_P4,  KC_P5, KC_P6, KC_PEQL,   \
    KC_P1,  KC_P2, KC_P3, KC_COMM,   \
    KC_LALT,  KC_P0, KC_PDOT, KC_PENT   \
),
[_NAV] = KEYMAP( /* Base */
  _______, _______, _______, _______,\
    KC_HOME,  KC_UP, KC_PGUP, _______,   \
    KC_LEFT,  XXXXXXX, KC_RIGHT, _______,   \
    KC_END,  KC_DOWN, KC_PGDN, _______,   \
    _______,  KC_INS, KC_DEL, _______   \
),
[_ALT] = KEYMAP( /* Base */
  _______, KC_MUTE, KC_VOLD, KC_VOLU,\
    _______,  _______, _______, _______,   \
    _______,  _______, _______, _______,   \
    _______,  _______, _______, _______,   \
    _______,  _______, _______, _______   \
),
[_ADJUST] = KEYMAP( /* Base */
  _______, KC_A, _______, RESET,\
    _______,  _______, _______, _______,   \
    _______,  _______, _______, _______,   \
    _______,  _______, _______, _______,   \
    _______,  _______, _______, _______   \
),
};

void numlock_led_on(void) {
  PORTF |= (1<<7);
}

void numlock_led_off(void) {
  PORTF &= ~(1<<7);
}

static bool numlock_down = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
	  case KC_NLCK:
      if (record->event.pressed) {
		  numlock_down = true;
		  if (IS_LAYER_ON(_ALT)) {
			  layer_on(_ADJUST);
		  }
	  } else{
		if(!IS_LAYER_ON(_ADJUST)) {
		  if (!IS_LAYER_ON(_NAV)){
			  numlock_led_off();
		    layer_on(_NAV);
		  } else {
			  numlock_led_on();
		    layer_off(_NAV);
		  }
		} else {
			layer_off(_ADJUST);
		}
		numlock_down = false;
	  } 
      return false;
      break;
	  case KC_LALT:
      if (record->event.pressed) {
		  if (numlock_down) {
			  layer_on(_ADJUST);
		  } else {
			  layer_on(_ALT);
		  }
	  } else {
		  if(IS_LAYER_ON(_ADJUST)) {
		      layer_off(_ADJUST);
		  } else {
			  layer_off(_ALT);
		  }
	  }
	  // Allow normal processing of ALT?
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
  // set Numlock LED to output and low
    DDRF |= (1<<7);
    PORTF &= ~(1<<7);

}

void matrix_scan_user(void) {

}


void led_set_user(uint8_t usb_led) {

}
