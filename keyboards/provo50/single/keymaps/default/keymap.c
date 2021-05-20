/* Copyright 2021 yushakobo
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

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    EISU = SAFE_RANGE,
    KANA,
    ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE
    * ,-----------------------------------------------------------.
    * |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |<- BS|
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |SHIFT|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ^  |ENTER|
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * | CTRL| GUI | ALT |SPACE|LOWER|RAISE|SPACE|  <  |  v  |  >  |
    * `-----------------------------------------------------------'
    */
    [_BASE] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,     KC_J,    KC_K,    KC_L,    KC_BSPC,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_UP,   KC_ENT,
        KC_LCTL, KC_LGUI, KC_LALT, EISU,   LOWER,   RAISE,     KANA,  KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    /* LOWER
    * ,-----------------------------------------------------------.
    * |  F1 |  F2 |  F3 |     |  -  |  +  |  \  |  F7 |  F8 |  F9 |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |  F4 |  F5 |  F6 |     |  [  |  ]  |  '  | F10 | F11 | F12 |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * | TAB |     |     |     |  ,  |  .  |  /  |     |     | DEL |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |SHIFT|     |     |     |     |     |     |     | PGUP|ENTER|
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * | CTRL| GUI | ALT |     |     |     |ENTER| HOME| PGDN| END |
    * `-----------------------------------------------------------'
    */
    [_LOWER] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_NO,   KC_MINS, KC_EQL,  KC_BSLS, KC_F7,    KC_F8,   KC_F9,
        KC_F4,   KC_F5,   KC_F6,   KC_NO,   KC_LBRC, KC_RBRC, KC_QUOT, KC_F10,   KC_F11,  KC_F12,
        KC_TAB,  _______, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, _______,  _______, KC_DEL,
        KC_LSFT, _______, _______, _______, _______, _______, _______, _______,  KC_PGUP, KC_ENT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  _______, _______,  KC_ENT,  KC_HOME, KC_PGDN, KC_END
    ),
    /* RAISE
    * ,-----------------------------------------------------------.
    * | ESC |     |     |     |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     | VOL+|     |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |     |     | ALT |ENTER|     |     |     |<PREV| VOL-|NEXT>|
    * `-----------------------------------------------------------'
    */
    [_RAISE] = LAYOUT(
        KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
        _______, _______, KC_LALT, KC_ENT,  _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    ),
    /* ADJUST (LOWER + RAISE)
    * ,-----------------------------------------------------------.
    * |     |     |     |     |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |     |     |
    * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
    * |     |     |     |     |     |     |     |     |     |     |
    * `-----------------------------------------------------------'
    */
    [_ADJUST] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EISU:
      if (record->event.pressed) {
        //pressed
        tap_code16(LALT(KC_GRAVE));
      } else {
        //released
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        //pressed
        tap_code16(LALT(KC_GRAVE));
      } else {
        //released
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        //pressed
        layer_on(_LOWER);
        layer_on(_RAISE);
      } else {
        //released
        layer_off(_LOWER);
        layer_off(_RAISE);
      }
      break;
      default:
      	return true; // Process all other keycodes normally
      break;
  }
  return true;
}
