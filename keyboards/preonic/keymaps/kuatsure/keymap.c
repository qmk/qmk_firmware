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
#include "kuatsure.h"

#define LAYOUT_preonic_grid_wrapper(...)   LAYOUT_preonic_grid(__VA_ARGS__)

enum preonic_layers {
  _QWERTY,
  _GAME,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum preonic_keycodes {
  QWERTY = USER_SAFE_RANGE,
  GAME,
  LOWER,
  RAISE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab/M|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc/C|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Leader| Game | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid_wrapper( \
  KC_GRV,  _________________NUMBER_L1_________________, _________________NUMBER_R1_________________, KC_BSPC, \
  KT_MTAB, _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_BSLS, \
  KT_CESC, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_QUOT, \
  KC_LSFT, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_ENT,  \
  QK_LEAD, GAME, KC_LALT, KC_LGUI, LOWER,       KC_SPC, KC_SPC,      RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT  \
),

/* Game
 *
 * Mostly transparent, but wanted to disable gui key.
 * Also give a key to get back to qwerty layout.
 *
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Qwerty|      |  Spc |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = LAYOUT_preonic_grid_wrapper( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, QWERTY,  _______, KC_SPC,  _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | E`~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |  Up  |      |   `  |   <  |   {  |   }  |  _   |      |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Del  | Left | Down | Right|   ~  |   =  |   (  |   )  |  +   |  :   |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Vol- | Prev | Play | Next | Vol+ |   -  |   [  |   ]  |  >   |  ?   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Mute |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid_wrapper( \
  QK_GESC, _________________SYMBOL_L1_________________,  _________________SYMBOL_R1_________________, _______, \
  _______, _______, _______, KC_UP,   _______,  KC_GRV,  _______, ____CRBRACES____, KC_UNDS, _______, KC_PIPE, \
  _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_TILD, KC_EQL,  _____PARENS_____, KC_PLUS, KC_COLN, KC_DQT , \
  _______, KC_VOLD, KC_MRWD, KC_MPLY, KC_MFFD,  KC_VOLU, KC_MINS, ___SQBRACKETS___, _______, KC_QUES, _______, \
  _______, KC_MUTE, _______, _______, _______,  _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |  *   |  7   |  8   |  9   |  0   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |  =   |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      |  -   |  1   |  2   |  3   |  /   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |  0   |  0   |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid_wrapper( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, \
  _______, ____________FUNCTION_3____________, _______, KC_ASTR, KC_7,    KC_8,    KC_9,    KC_0,     _______, \
  _______, ____________FUNCTION_2____________, _______, KC_EQL,  KC_4,    KC_5,    KC_6,    KC_PLUS,  _______, \
  _______, ____________FUNCTION_1____________, _______, KC_MINS, KC_1,    KC_2,    KC_3,    KC_SLASH, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_0,    _______,  _______  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | MAKE | FLSH |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Boot | Debug|      |      |Aud on|AudOff|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | VRSN |      |      |MusMod|Mus on|MusOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |Qwerty| Game |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid_wrapper( \
  ____________FUNCTION_1____________, ____________FUNCTION_2____________, ____________FUNCTION_3____________, \
  _______, KB_MAKE, KB_FLSH, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  \
  _______, QK_BOOT, DB_TOGG, _______, _______, AU_ON,   AU_OFF,  _______, _______, _______, _______, _______, \
  _______, KB_VRSN, _______, _______, MU_MOD,  MU_ON,   MU_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,  GAME,    _______, _______  \
),

};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;

    case GAME:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAME);
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
};
