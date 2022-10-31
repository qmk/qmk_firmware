/* Copyright 2020 Toyoshima Hidenori <t@toyo.dev>
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
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
};

#define EISU LALT(KC_GRV)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  TAB |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |   [  |                    |   ]  |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |  GUI |                    |  GUI |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  ESC |  ALt | ESC  |||||||| Shift| Raise| Space|||||||| enter| Lower| Bcspc|||||||| Left | Down |  Up  | Right|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
    [_QWERTY] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,                        KC_EQL , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                        KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI,                        KC_RGUI, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_ESC,  KC_LALT, KC_ESC,           KC_LSFT, RAISE,   KC_SPC,        KC_ENT, LOWER,   KC_BSPC,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |   ~  |   1  |   2  |   3  |   4  |   5  |   _  |                    |   +  | 6    | 7    |  8   | 9    |   0  |   |  |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Ctrl |   ^  |   &  |   *  |   (  |   )  |   {  |                    |   }  | Left | Down |  Up  | Right|   :  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   !  |   @  |   #  |   $  |   %  |  GUI |                    |  GUI |   -  |   =  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  ESC |  ALt | EISU |||||||| kana | Raise| Space|||||||| Enter| Lower|Delete|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_UNDS,                       KC_PLUS, KC_6,    KC_7,    KC_8,   KC_9,    KC_0,    KC_PIPE,
    KC_LCTL, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_LCBR,                       KC_RCBR, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_COLN, KC_DQT ,
    KC_LSFT, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LGUI,                       KC_RGUI, KC_MINS, KC_EQL,  KC_LT,  KC_GT,   KC_QUES, KC_RSFT,
    KC_LCTL, KC_ESC, KC_LALT,  KC_LNG2,          KC_LNG1, RAISE,   KC_SPC,       KC_ENT, LOWER,   KC_DEL,           KC_HOME,KC_PGDN, KC_PGUP, KC_END
  ),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |   _  |                    |   +  | 6    | 7    |  8   | 9    |   0  |   |  |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Ctrl |   ^  |   &  |   *  |   (  |   )  |   {  |                    |   }  | Left | Down |  Up  | Right|   :  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   !  |   @  |   #  |   $  |   %  |  GUI |                    |  GUI |   _  |   +  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  ESC |  ALt | EISU |||||||| kana | Raise| Space|||||||| Enter| Lower|Delete|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
  */
  [_RAISE] = LAYOUT(
    KC_GRV , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_UNDS,                       KC_PLUS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PIPE,
    KC_LCTL, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_LCBR,                       KC_RCBR, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_COLN, KC_DQT ,
    KC_LSFT, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LGUI,                       KC_RGUI, KC_UNDS, KC_PLUS, KC_LT,   KC_GT,   KC_QUES, KC_RSFT,
    KC_LCTL, KC_ESC,  KC_LALT, KC_LNG2,          KC_LNG1, RAISE,   KC_SPC,       KC_ENT, LOWER,   KC_DEL,           KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |                                  |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |                    |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, QK_BOOT, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______,
    _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC ,_______,                       _______, _______, _______, _______, _______, _______, _______,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6 ,_______,                       _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
