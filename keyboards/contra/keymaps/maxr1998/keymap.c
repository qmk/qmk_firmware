/* Copyright 2015-2017 Jack Humbert
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

#include "contra.h"
#include "keymap_german.h"

enum contra_layers {
  _QWERTZ,
  _FUNC,
  _NUMPAD,
  _NUMROW
};

#define FUN MO(_FUNC)
#define NPK TT(_NUMPAD)
//#define SPEC_S LM(_NUMROW, (KC_LSFT))
//#define SPEC_L3 LM(_NUMROW, (DE_ALGR))

enum custom_keycodes {
    SPEC_S = SAFE_RANGE,
    SPEC_L3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwertz
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | +* ~ | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Sup  | Alt  | NumP | Spec |    Space    | Sp_A | Fun  | Left | Down | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTZ] = {
  {KC_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    DE_PLUS, KC_ENT },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT},
  {KC_LCTL, KC_LGUI, KC_LALT, NPK,     SPEC_S,  KC_SPC,  KC_SPC,  SPEC_L3, FUN,     KC_LEFT, KC_DOWN, KC_RGHT}
},

/* Function layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   Ü  |      |   Ö  |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Lock |   Ä  |      |      |      |      |      | RGBS | RGBB | RGBS |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | RGBH-| RGBT | RGBH+| PgUp |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ---- | ---- |      |      | ---- | ---- | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = {
  {_______, _______, _______, _______, _______, _______, _______, DE_UE,   _______, DE_OE,   _______, KC_DEL },
  {KC_LOCK, DE_AE,   _______, _______, _______, _______, _______, RGB_M_P, RGB_M_B, RGB_M_SW,_______, _______},
  {_______, _______, _______, _______, _______, _______, _______, RGB_HUD, RGB_TOG, RGB_HUI, KC_PGUP, _______},
  {_______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_END }
},

/* Numrow layer (special characters with Shift and ISO_L3_Shift)
 * ,-----------------------------------------------------------------------------------.
 * |      |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   |  ß   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  ><| |      |      |      |      |      |      |      |      | _  - |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ---- | ---- |      |      | ---- | ---- |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMROW] = {
  {_______, DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    DE_SS  },
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, DE_LESS, _______, _______, _______, _______, _______, _______, _______, _______, DE_MINS, _______},
  {_______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______}
},

/* Numpad layer
 * ,-----------------------------------------------------------------------------------.
 * |      |  +   |  7   |  8   |  9   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  -   |  4   |  5   |  6   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  *   |  1   |  2   |  3   |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  /   |  0   | ---- | ---- |      |      | ---- | ---- |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = {
  {DEBUG,   KC_PPLS, KC_P7,   KC_P8,   KC_P9,   _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_PMNS, KC_P4,   KC_P5,   KC_P6,   _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_PAST, KC_P1,   KC_P2,   KC_P3,   _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_PSLS, KC_P0,   _______, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______}
}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SPEC_S:
    if (record->event.pressed) {
      register_code(KC_LSFT);
      layer_on(_NUMROW);
    } else {
      layer_off(_NUMROW);
      unregister_code(KC_LSFT);
    }
    return false;
    case SPEC_L3:
    if (record->event.pressed) {
      register_code(DE_ALGR);
      layer_on(_NUMROW);
    } else {
      layer_off(_NUMROW);
      unregister_code(DE_ALGR);
    }
    return false;
    default:
    return true;
  }
}

void led_set_user(uint8_t usb_led) {
  // Force-enable Numlock
  if (!(usb_led & (1<<USB_LED_NUM_LOCK))) {
    register_code(KC_NUMLOCK);
    unregister_code(KC_NUMLOCK);
  }
}
