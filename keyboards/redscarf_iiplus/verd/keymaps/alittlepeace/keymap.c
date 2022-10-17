/* Copyright 2019 Andy Lee <alee@alittlepeacemusic.com>
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
    KC_P00 = SAFE_RANGE,
    
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_60_ansi_numpad_split0(
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, TG(1), KC_PSLS, KC_PAST, KC_PMNS, 
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_INS, KC_HOME, KC_PGUP, 
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_DEL, KC_END, KC_PGDN, KC_PPLS, 
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, C(S(KC_TAB)), KC_UP, LCTL(KC_TAB), 
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, KC_RGUI, MO(2), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PENT
    ),

    [1] = LAYOUT_60_ansi_numpad_split0(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_4,    KC_5,    KC_6,    _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_1,    KC_2,    KC_3,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, KC_0,    KC_P00,  KC_DOT,  _______
    ),
    
    [2] = LAYOUT_60_ansi_numpad_split0(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______
    ),
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_P00:
            if (record->event.pressed) {
                SEND_STRING("00");
                 }
        break;
         case TG(1):
           if (record->event.pressed) {
                tap_code(KC_NUM_LOCK);
		return true;
		}
	   break;

    }
    return true;
}

void matrix_init_user (void) {
  if (!host_keyboard_led_state ().num_lock) {
      tap_code(KC_NUM_LOCK);
  }
}

bool led_update_user(led_t led_state) {
    if (led_state.num_lock) {
        layer_on(1);
    } else {
        layer_off(1);
    }
    return true;
}
