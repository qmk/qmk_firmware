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

#include "planck.h"
#include "action_layer.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define SP_LESS LSFT(KC_COMMA)
#define SP_MORE LSFT(KC_DOT)
#define SP_SPC  MT(MOD_LSFT, KC_SPC)

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _AZERTY,
  _GAMING,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FN
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  AZERTY,
  GAMING,
  LOWER,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------------------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  | Up   |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Fn   | Alt  |Lower |Shift & Space|Raise | Alt  | Left | Down |Right |
   * `-----------------------------------------------------------------------------------'
   */
  [_QWERTY] = {
    {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT},
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_UP,   KC_RSFT},
    {KC_LCTL, KC_LGUI, MO(_FN), KC_LALT, LOWER, SP_SPC, SP_SPC, RAISE, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT}
  },

  /* Azerty
   * ,-----------------------------------------------------------------------------------.
   * | Esc  |   A  |   Z  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Tab  |   Q  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   M  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   W  |   X  |   C  |   V  |   B  |   N  |   ,  |   ;  |   :  | Up   |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Fn   | Alt  |Lower |Shift & Space|Raise | Alt  | Left | Down |Right |
   * `-----------------------------------------------------------------------------------'
   */
  [_AZERTY] = {
    {KC_ESC,  KC_A,    KC_Z,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_TAB,  KC_Q,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_M,    KC_ENT},
    {KC_LSFT, KC_W,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_COMM, KC_SCLN, KC_COLN, KC_UP,   KC_RSFT},
    {KC_LCTL, KC_LGUI, MO(_FN), KC_LALT, LOWER, SP_SPC, SP_SPC, RAISE,   KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT}
  },

  /* Gaming
   * ,-----------------------------------------------------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  | Up   |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  |Space |Lower |Shift & Space|Raise | Fn   | Left | Down |Right |
   * `-----------------------------------------------------------------------------------'
   */
  [_GAMING] = {
    {KC_ESC,  KC_Q,    KC_W,    KC_E,   KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_TAB,  KC_A,    KC_S,    KC_D,   KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT},
    {KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_UP,   KC_RSFT},
    {KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, LOWER, SP_SPC, SP_SPC, RAISE, MO(_FN), KC_LEFT, KC_DOWN, KC_RGHT}
  },

  /* Lower
   * ,-----------------------------------------------------------------------------------.
   * |   ^  |   @  |   #  |   $  |   %  |   &  |   *  |   _  |   -  |   +  |   =  | Del  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |  `   |   '  |   {  |   [  |   (  |   !  |   ?  |   )  |   ]  |   }  |   "  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |   |  |   /  |   <  |   >  |   \  |   |  |      | PgUp |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      | Home |PgDwn | End  |
   * `-----------------------------------------------------------------------------------'
   */
  [_LOWER] = {
    {KC_CIRC, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_AMPR, KC_ASTR, KC_UNDS, KC_MINS, KC_PLUS, KC_EQUAL, KC_DELETE},
    {KC_GRV,  KC_QUOT, KC_LCBR, KC_LBRC, KC_LPRN, KC_EXLM, KC_QUES, KC_RPRN, KC_RBRC, KC_RCBR, KC_DQT,   _______},
    {_______, _______, _______, KC_PIPE, KC_SLSH, SP_LESS, SP_MORE, KC_BSLS, KC_PIPE, _______, KC_PGUP,  _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN,  KC_END}
  },

  /* Raise
   * ,-----------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_RAISE] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
    {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
  },

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |qwerty|azerty|gaming|      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_ADJUST] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, QWERTY,  AZERTY,  GAMING,  _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
  },

  /* Misc Functions
   * ,-----------------------------------------------------------------------------------.
   * |reset |      |      |      |      |      |      |      |      |      |      |prtscr|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      | vol+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | play | vol- |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      | prev | paus | next |
   * `-----------------------------------------------------------------------------------'
   */
  [_FN] = {
    {RESET,   _______ ,_______ ,_______ ,_______, _______, _______, _______, _______, _______, _______, KC_PSCREEN},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT}
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to the qwerty layout\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case AZERTY:
      if (record->event.pressed) {
        print("mode just switched to the azerty layout\n");
        set_single_persistent_default_layer(_AZERTY);
      }
      return false;
      break;
    case GAMING:
      if (record->event.pressed) {
        print("mode just switched to the gaming layout\n");
        set_single_persistent_default_layer(_GAMING);
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
