/* Copyright 2017 Balz Guenat
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
  WIN_SWITCH_LAYOUT = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
-------------------------------------------------------------------------------------------
|GvEsc|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  | Backspace |
-------------------------------------------------------------------------------------------
|  Tab   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   \    |
-------------------------------------------------------------------------------------------
|   Fn1   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |    Enter    |
-------------------------------------------------------------------------------------------
|    Shift    |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |  Shift  |M(0) |
-------------------------------------------------------------------------------------------
| Ctrl  |  GUI  |  Alt  |   Space    |  Fn1  |   Space    |  Alt  |  GUI  |  App  | Ctrl  |
-------------------------------------------------------------------------------------------
*/
[0] = LAYOUT_base( \
    KC_GESC, KC_1,    KC_2,    KC_3, KC_4,   KC_5,  KC_6,   KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R,   KC_T,  KC_Y,   KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
    MO(1),   KC_A,    KC_S,    KC_D, KC_F,   KC_G,  KC_H,   KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
    KC_LSFT,          KC_Z,    KC_X, KC_C,   KC_V,  KC_B,   KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, WIN_SWITCH_LAYOUT,\
    KC_LCTL, KC_LGUI, KC_LALT,       KC_SPC, MO(1), KC_SPC,       KC_RALT, KC_RGUI, KC_NO,   KC_APP,  KC_RCTL \
),
/*
-------------------------------------------------------------------------------------------
|     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |           |
-------------------------------------------------------------------------------------------
| CpsLck |Prev |Vol+ |Next |PgUp | Ins |Home |WrdL |WrdR | End |     |     |     | PrtSc  |
-------------------------------------------------------------------------------------------
|  TRNS   |Mute |Vol- |Play |PgDn | Del |Left |Down | Up  |Right|     |     |             |
-------------------------------------------------------------------------------------------
|             |     |     |     |     |     |DelWL|DelWR|     |     |     |         |     |
-------------------------------------------------------------------------------------------
|       |       |       |            | TRNS  |            |       |       |       | Reset |
-------------------------------------------------------------------------------------------
*/
[1] = LAYOUT_base( \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,   KC_F7,         KC_F8,         KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
    KC_CAPS, KC_MPRV, KC_VOLU, KC_MNXT, KC_PGUP, KC_INS, KC_HOME, LCTL(KC_LEFT), LCTL(KC_RGHT), KC_END,  _______, _______, _______, KC_PSCR, \
    _______, KC_MUTE, KC_VOLD, KC_MPLY, KC_PGDN, KC_DEL, KC_LEFT, KC_DOWN,       KC_UP,         KC_RGHT, _______, _______, _______, \
    _______,          BL_STEP, BL_BRTG, _______, _______,_______, LCTL(KC_BSPC), LCTL(KC_DEL),  _______, _______, _______, _______, _______, \
    _______, _______, _______,          _______, _______,_______,                _______,       _______, _______, _______, RESET \
),
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case WIN_SWITCH_LAYOUT: {
      // Sends Alt+Shift on both key down and key up.
      // Designed to switch between two keyboard layouts on Windows using a locking switch.
      // Does nothing if right shift is pressed for easy resync.
      if (!(get_mods() & MOD_BIT(KC_RSFT)))
        SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_LSHIFT)SS_UP(X_LALT));
      return false;
    }

    default:
      return true;
  }
}

void led_set_user(uint8_t usb_led) {

}
