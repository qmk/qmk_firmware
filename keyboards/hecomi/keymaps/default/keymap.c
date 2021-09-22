/* Copyright 2018 takashiski
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

//R1:7 + 8 = 15
//R2:7 + 8 = 15
//R3:6 + 7 = 13
//R4:6 + 8 = 14
//R5:6 + 6 = 12
//total : 69 keys
//
enum layers{
	DF,
	FN
};

#define KC_FN MO(FN)
#define KC_SFT(XXX) LSFT(XXX)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[DF]=LAYOUT(\
			KC_ESC,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,                  KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_NUHS,KC_GRV,\
			KC_TAB  ,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,                 KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,KC_BSPC,\
			KC_LCTRL ,KC_A,KC_S,KC_D,KC_F,KC_G,                     KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_ENT,\
			KC_LSFT   ,KC_Z,KC_X,KC_C,KC_V,KC_B,               KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_FN,\
			KC_LCTRL,KC_LGUI,KC_LALT,KC_MHEN,KC_BSPC,KC_SPC,  KC_ENT,KC_ESC,KC_HENK,KC_RALT,KC_RGUI,KC_RCTRL\
			),
	[FN]=LAYOUT(\
			KC_ESC,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,                  KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_INS,KC_DEL,\
			KC_TAB  ,KC_9,KC_7,KC_5,KC_3,KC_1,KC_Y,                 KC_Y,KC_U,KC_PSCR,KC_SLCK,KC_PAUSE,KC_UP,KC_RBRC,KC_BSPC,\
			KC_CAPS ,KC_8,KC_6,KC_4,KC_2,KC_0,                     KC_SFT(KC_8),KC_SLSH,KC_HOME,KC_PGUP,KC_LEFT,KC_RIGHT,KC_ENT,\
			KC_LSFT   ,KC_Z,KC_X,KC_C,KC_V,KC_B,               KC_B,KC_SFT(KC_EQL),KC_MINS,KC_END,KC_PGDN,KC_DOWN,KC_RSFT,KC_TRNS,\
			KC_LCTRL,KC_LGUI,KC_LALT,KC_MHEN,KC_BSPC,KC_SPC,  KC_ENT,KC_ESC,KC_HENK,KC_RALT,KC_RGUI,KC_RCTRL\
			),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state)
{
	uint8_t layer=get_highest_layer(state);
	switch(layer)
	{
		case DF:
			rgblight_sethsv_noeeprom(180,255,255);
			break;
		case FN:
			rgblight_sethsv_noeeprom(0,255,255);
			break;
		default:
			break;
	}
	return state;
}
