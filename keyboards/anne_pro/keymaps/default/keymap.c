/* Copyright 2019 Michiel Visser
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

/* Custom keycodes for the lighting control for the Anne Pro */
enum my_keycodes {
  ANNERGB = SAFE_RANGE,
  ANNERAT,
  ANNEBRT,
  ANNEMOD
};

/* Default Anne Pro layout, macOS style with LALT and LWIN switched */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,
      KC_LCTL, KC_LALT, KC_LWIN,                   KC_SPACE,                                    KC_RALT, MO(1),   KC_NO,   KC_RCTL
  ),
  [1] = LAYOUT(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
      _______, _______, KC_UP,   _______, ANNERGB, ANNERAT, ANNEBRT, ANNEMOD, KC_UP,   KC_SLCK, KC_PAUS, KC_HOME, KC_END,  KC_PSCR,
      _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, KC_PGDN,          _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_DEL,                    _______,
      _______, _______, _______,                   _______,                                     _______, _______, _______, _______
  )
};

/* State of the leds on the keyboard */
volatile bool leds_enabled = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ANNERGB:
        /* Toggle the RGB enabled/disabled */
        if (record->event.pressed) {
            leds_enabled = !leds_enabled;
            if (leds_enabled) {
                uartStartSend(&UARTD3, 3, "\x09\x01\x01");
            } else {
                uartStartSend(&UARTD3, 4, "\x09\x02\x01\x00");
            }
        }
        return false;
    case ANNERAT:
        /* Change the animation rate */
        if (leds_enabled && record->event.pressed) {
            uartStartSend(&UARTD3, 6, "\x09\x04\x05\x00\x01\x00");
        }
        return false;
    case ANNEBRT:
        /* Change the brightness */
        if (leds_enabled && record->event.pressed) {
            uartStartSend(&UARTD3, 6, "\x09\x04\x05\x00\x00\x01");
        }
        return false;
    case ANNEMOD:
        /* Change the lighting mode */
        if (leds_enabled && record->event.pressed) {
            uartStartSend(&UARTD3, 6, "\x09\x04\x05\x01\x00\x00");
        }
        return false;
    default:
        /* Handle other keycodes normally */
        return true;
    }
}
