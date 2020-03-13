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

#include QMK_KEYBOARD_H
#include "keymap_extras/keymap_german.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  LOWER,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/**
,-----------------------------------------------------------------------------------.
 | ESC  |   Ü  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   T  |   Z  | Bksp |
 |------+------+------+------+------+-------------+------+------+------+------+------|
 | TAB  |   A  |   O  |   E  |   I  |   U  |   H  |   D  |   R  |   N  |   S  |  L   |
 |------+------+------+------+------+------|------+------+------+------+------+------|
 | Shift|   Ä  |   Ö  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |Enter |
 |------+------+------+------+------+------+------+------+------+------+------+------|  
 | CTRL |  GUI | Alt  | MOD  |Lower |   Space     |Raise | Left |Right |  Up  |Down  |
 `-----------------------------------------------------------------------------------'
**/
  [_DVORAK] = LAYOUT_planck_mit(
    KC_ESC,  DE_UE,   DE_COMM,    DE_DOT,    DE_P,    DE_Y,    DE_F,    DE_G,    DE_C,    DE_T,    DE_Z,    KC_BSPC,
    KC_TAB, DE_A,   DE_O,    DE_E,    DE_I,    DE_U,    DE_H,    DE_D,    DE_R,    DE_N,    DE_S, DE_L,
    KC_LSFT, DE_AE,   DE_OE,    DE_Q,    DE_J,    DE_K,    DE_X,    DE_B,    DE_M, DE_W,  DE_V, KC_ENT ,
    KC_LCTL,  KC_LGUI, KC_LALT, MO(3), LOWER, KC_SPC, RAISE,   KC_LEFT, KC_RIGHT, KC_UP,   KC_DOWN
  ),

  /* Lower
   * ,-----------------------------------------------------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
   * `-----------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_planck_mit(
    DE_TILD, DE_EXLM, DE_AT,   DE_HASH, DE_DLR,  DE_PERC, DE_CIRC, DE_AMPR,    DE_ASTR,    DE_LPRN, DE_RPRN, KC_DEL,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   DE_UNDS,    DE_PLUS,    DE_LCBR, DE_RCBR, DE_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  DE_QST,
    _______, _______, _______, _______, _______,     _______,      _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
  ),

  /* Raise
   * ,-----------------------------------------------------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
   * `-----------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_planck_mit(
    DE_GRV,  DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    KC_DEL,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   DE_MINS, DE_EQL,  DE_LBRC, DE_RBRC, DE_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, DE_SLSH,
    _______, _______, _______, _______, _______,     _______,      _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
  ),

  /* Adjust (MO(3))
   * ,-----------------------------------------------------------------------------------.
   * |      | HOME |  UP  |  END |      |      |      |      |      |      |      |  Del |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |      | LEFT | DOWN | RIGHT|      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |             |      |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_ADJUST] = LAYOUT_planck_mit(
    _______, KC_HOME, KC_UP, KC_END, _______, _______, _______, _______, _______, _______, _______, KC_DEL ,
    _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______,  _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        print("mode just switched to dvorak and this is a huge string\n");
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
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
  }
  return true;
}
