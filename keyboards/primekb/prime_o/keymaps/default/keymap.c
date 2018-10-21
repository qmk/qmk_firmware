/* Copyright 2018 Jumail Mundekkat
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
		KC_ENT, KC_P0, KC_LCTL, KC_LBRC, LT(1, KC_BSPC), KC_SPC, KC_MINS, KC_RGUI, 
		KC_ENT, KC_P2, KC_LSFT, KC_X, KC_V, KC_N, KC_COMM, KC_SLSH, 
		KC_PPLS, KC_P5, KC_TAB, KC_S, KC_F, KC_H, KC_K, KC_QUOT, 
		KC_PPLS, KC_P8, KC_PSCR, KC_W, KC_R, KC_Y, KC_I, KC_P, 
		KC_ESC, KC_PSLS, KC_NLCK, KC_2, KC_4, KC_6, KC_8, KC_0, 
		KC_PMNS, KC_PAST, KC_1, KC_3, KC_5, KC_7, KC_9, KC_DEL, 
		KC_P7, KC_P9, KC_Q, KC_E, KC_T, KC_U, KC_O, KC_BSLS, 
		KC_P4, KC_P6, KC_A, KC_D, KC_G, KC_J, KC_L, KC_ENT, 
		KC_P1, KC_P3, KC_Z, KC_C, KC_B, KC_M, KC_DOT, KC_LSFT, 
		KC_PDOT, KC_P0, KC_LALT, KC_RBRC, LT(1, KC_BSPC), KC_SPC, KC_EQL, KC_RCTL
    ),

	[1] = LAYOUT(
		BL_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_VOLD, KC_MUTE, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DOWN, KC_SCLN, 
		KC_TRNS, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, 
		KC_GRV, KC_F2, KC_F4, KC_F2, KC_F4, KC_F6, KC_F8, KC_F10, 
		KC_F1, KC_F3, KC_F1, KC_F3, KC_F5, KC_F7, KC_F9, KC_DEL, 
		KC_F11, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_RGHT, KC_VOLU, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE, 
		BL_STEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_VOLU, KC_MUTE
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

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
