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
    CTRLMA,
    LAYEON,
    LAYOFF

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_60_numpad(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, LAYEON, KC_PSLS, KC_PAST, KC_PMNS, 
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_INS, KC_HOME, KC_PGUP, 
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_DEL, KC_END, KC_PGDN, KC_PPLS, 
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, 
        CTRLMA, KC_UP, LCTL(KC_TAB), KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, KC_RGUI, KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PENT
    ),

    [1] = LAYOUT_60_numpad(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LAYOFF, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_P00, KC_DOT, KC_TRNS),

};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_P00:
            if (record->event.pressed) {
                SEND_STRING("00");
                 }
            break;
        case CTRLMA:
            if (record->event.pressed) {
		tap_code16(C(S(KC_TAB)));
		 }
	    break;
	    case TG(1):
           if (record->event.pressed) {
                tap_code(KC_NUMLOCK);
		return true;
		}
	    break;
	    case LAYOFF:
	    if (record->event.pressed) {
		tap_code(KC_NUMLOCK);
		layer_invert(1);
		}
	    break;
    }
    return true;
}

void matrix_init_user (void) {
  if (!IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {
      tap_code(KC_NUMLOCK);
  }
}

void led_set_user(uint8_t usb_led) {
    if(IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        layer_on(1);
    } else {
        layer_off(0);
    }
}
