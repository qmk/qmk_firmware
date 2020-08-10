/* Copyright 2019 takashiski
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

enum layers{
    BOOTMAGIC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BOOTMAGIC] = LAYOUT(
			KC_R,KC_R,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,             KC_F6, KC_F7,  KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,KC_L,KC_L,
			KC_TAB,   KC_Q,  KC_UP,  KC_E,  KC_R,  KC_T,  KC_Y,      KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_LBRC,KC_RBRC,KC_SPC,
			KC_SPC,  KC_BSPACE,  KC_ESC,  KC_RIGHT,  KC_F,  KC_G,                    KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT,  KC_ESC,  KC_BSPACE,KC_SPC,
			KC_LSHIFT,KC_HOME,  KC_END,  KC_PGUP,  KC_PGDN,  KC_INSERT,             KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT, KC_END,KC_UP,KC_HOME,
			KC_L, KC_L,KC_LALT,KC_MHEN,KC_SPC,KC_SPC,KC_SPC,        KC_SPC,KC_SPC,KC_SPC,KC_HENK,KC_TRNS,KC_LEFT,KC_R,KC_R
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
