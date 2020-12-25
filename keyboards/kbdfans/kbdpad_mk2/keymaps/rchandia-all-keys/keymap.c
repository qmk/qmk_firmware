/* Copyright 2019 Ryota Goto
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_6x4( /* Base */
    KC_ESC,  KC_LBRC, KC_RBRC, KC_BSPC,
	KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
	KC_P7,   KC_P8,   KC_P9,   KC_TAB ,
	KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
	KC_P1,   KC_P2,   KC_P3,   KC_PENT,
	KC_P0,   KC_COMM, KC_PDOT, MO(1)
  ),
  [1] = LAYOUT_ortho_6x4( /* Layer 1: Control */
    _______, KC_LCBR, KC_RCBR, XXXXXXX,
    XXXXXXX, BL_TOGG, BL_STEP, XXXXXXX,
    RGB_TOG, RGB_MOD, RGB_RMOD,RGB_HUI,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_SPC,  KC_SCLN, KC_COLN, XXXXXXX
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
