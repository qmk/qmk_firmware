/* Copyright 2018 Yiancar
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

enum custom_keycodes {
    KC_P00 = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_5x4(
    TG(1),   KC_PSLS, KC_PAST, KC_PMNS, \
    KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS, \
    KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
    KC_P0,   KC_P00,  KC_PDOT, KC_PENT  \
  ),

  [1] = LAYOUT_ortho_5x4(
    _______, _______, _______, _______, \
    KC_HOME, KC_UP,   KC_PGUP, _______, \
    KC_LEFT, XXXXXXX, KC_RGHT, _______, \
    KC_END,  KC_DOWN, KC_PGDN, _______, \
    KC_INS,  XXXXXXX, KC_DEL,  _______  \
  ),
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case KC_P00:
                // types Numpad 0 twice
                SEND_STRING(SS_TAP(X_KP_0) SS_TAP(X_KP_0));
                return false;
        }
    }
    return true;
};

void led_set_user(uint8_t usb_led) {

}
