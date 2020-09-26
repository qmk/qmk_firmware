/* Copyright 2018
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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER  1

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,---------------------------------------------------------------------.
   * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |
   * |------+------+------+------+------+------+------+------+------+------|
   * |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |
   * |------+------+------+------+-------------+------+------+------+------|
   * |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | Bksp |
   * |------+------+------+------+------|------+------+------+------+------|
   * |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |Enter |
   * |------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  |Lower |Space | Shift| Left | Down |  Up  |Right |
   * `---------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_split(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_BSPC, \
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_ENT,  \
    KC_LCTL, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_LSFT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
  ),

  /* Lower
   * ,---------------------------------------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  `   |   /  |   _  |   +  |
   * |------+------+------+------+------|------+------+------+------+------|
   * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  ~   |   [  |   ]  |  \   |
   * |------+------+------+------+-------------+------+------+------+------|
   * | Esc  |      |      |      |      |      |      |   ;  |  "   |  Del |
   * |------+------+------+------+------|------+------+------+------+------|
   * | Tab  |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
   * `---------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_split( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_GRV, KC_SLSH, KC_UNDS, KC_PLUS, \
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TILD, KC_LBRC, KC_RBRC, KC_PIPE, \
    KC_ESC,  _______, _______, _______, _______, _______, _______, KC_SCLN, KC_QUOT, KC_DEL,  \
    KC_TAB,  _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
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
