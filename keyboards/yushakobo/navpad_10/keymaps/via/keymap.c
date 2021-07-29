/* Copyright 2021 yushakobo
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

#define LOCK_COLOR_1 HSV_TEAL

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { 
  NONE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] =LAYOUT (\
    KC_PSCR,   KC_SLCK,   KC_PAUS,   KC_1,\
	  KC_INS,    KC_HOME,   KC_PGUP,   KC_ESC,    KC_PSLS,    KC_PAST,   KC_PMNS,\
  	KC_DEL,    KC_END,    KC_PGDN,   KC_P7,     KC_P8,      KC_P9,     KC_PPLS,\
                                     KC_P4,     KC_P5,      KC_P6,     KC_PPLS,\
  	S(KC_TAB), KC_UP,     KC_TAB,    KC_P1,     KC_P2,      KC_P3,     LT(1,KC_PENT),\
  	KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_P0,     KC_P0,      KC_PDOT,   LT(1,KC_PENT) \
    ),

    [_FN1] =LAYOUT (\
  	RESET,     EEP_RST,   KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NLCK,   KC_QUOT,   KC_NO,      KC_NO,\
  	KC_CAPS,   KC_NLCK,   KC_SLCK,   S(KC_9),   KC_UP,     S(KC_0),    S(KC_SPC),\
                                     KC_LEFT,   KC_NO,     KC_RGHT,    S(KC_SPC),\
  	KC_TRNS,   S(KC_ENT), KC_TRNS,   KC_BSPC,   KC_DOWN,   KC_DEL,     KC_TRNS,\
  	KC_BTN1,   KC_ENT,    S(KC_SPC), KC_PEQL,   KC_PEQL,   KC_NO,      KC_TRNS \
    ),

    [_FN2] =LAYOUT (\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,\
                                     KC_NO,     KC_NO,     KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO \
    ),

    [_FN3] =LAYOUT (\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,\
                                     KC_NO,     KC_NO,     KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,\
  	KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO \
    )
};

//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//}

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code16(KC_WH_U);
    } else {
      tap_code16(KC_WH_D);
    }
  }
  return false;
}

const rgblight_segment_t PROGMEM navpad10_capslock[] = RGBLIGHT_LAYER_SEGMENTS(
  {4, 1, LOCK_COLOR_1}
);

const rgblight_segment_t PROGMEM navpad10_numlock[] = RGBLIGHT_LAYER_SEGMENTS(
  {0, 1, LOCK_COLOR_1},
  {5, 1, LOCK_COLOR_1}
);

const rgblight_segment_t PROGMEM navpad10_scrolllock[] = RGBLIGHT_LAYER_SEGMENTS(
  {2, 1, LOCK_COLOR_1},
  {8, 1, LOCK_COLOR_1}
);

void led_set_user(uint8_t usb_led) {
  rgblight_set_layer_state(0, host_keyboard_led_state().caps_lock);
  rgblight_set_layer_state(1, host_keyboard_led_state().num_lock);
  rgblight_set_layer_state(2, host_keyboard_led_state().scroll_lock);
}