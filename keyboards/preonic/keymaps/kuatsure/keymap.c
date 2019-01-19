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

enum preonic_layers {
  _QWERTY,
  _GAME,
  _GAME_MOD,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  GAME,
  GAME_MOD,
  LOWER,
  RAISE,

  END_OF_LINE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
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
  KC_TAB,  _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_BSLS, \
  KT_CESC, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_QUOT, \
  KC_LSFT, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_ENT,  \
  KC_LEAD, GAME, KC_LALT, KC_LGUI, LOWER,       KC_SPC, KC_SPC,      RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT  \
),

/* Game
 *
 * Mostly transparent, but wanted to disable gui key, and give different raise / lower layers ( game_mod ).
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
 * |      |Qwerty|      |  Spc |Game+ |             |Game+ |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = LAYOUT_preonic_grid_wrapper( \
  _______, _______, _______, _______, _______,  _______, _______, _______,  _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,  _______, _______, _______,  _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,  _______, _______, _______,  _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,  _______, _______, _______,  _______, _______, _______, _______, \
  _______, QWERTY,  _______, KC_SPC,  GAME_MOD, _______, _______, GAME_MOD, _______, _______, _______, _______  \
),

/* Game Modifiers
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |  `   |      |  7   |  8   |  9   |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |  ~   |      |  4   |  5   |  6   |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |  F1  |  F2  |  F3  |  F4  |      |      |  1   |  2   |  3   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |  0   |  0   |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME_MOD] = LAYOUT_preonic_grid_wrapper( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, ____________FUNCTION_3____________, KC_GRV,  _______, KC_7,    KC_8,    KC_9,    _______, _______, \
  _______, ____________FUNCTION_2____________, KC_TILD, _______, KC_4,    KC_5,    KC_6,    _______, _______, \
  KC_LSFT, ____________FUNCTION_1____________, _______, _______, KC_1,    KC_2,    KC_3,    _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_0,    _______, _______  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |  Up  |      |   `  |      |   {  |   }  |  _   |      |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Del  | Left | Down | Right|   ~  |   =  |   (  |   )  |  +   |  :   |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Vol- | Prev | Play | Next | Vol+ |   -  |   [  |   ]  |      |  ?   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Mute |      |      |      |             |      | Home | PgUp | PgDwn| End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid_wrapper( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
  _______, _______, _______, KC_UP,   _______,  KC_GRV,  _______, KC_LCBR, KC_RCBR, KC_UNDS, _______, KC_PIPE, \
  _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_TILD, KC_EQL,  KC_LPRN, KC_RPRN, KC_PLUS, KC_COLN, KC_DQT , \
  _______, KC_VOLD, KC_MRWD, KC_MPLY, KC_MFFD,  KC_VOLU, KC_MINS, KC_LBRC, KC_RBRC, _______, KC_QUES, _______, \
  _______, KC_MUTE, _______, _______, _______,  _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END   \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | E`~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |   {  |   }  |      |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      |   (  |   )  |   <  |   >  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |   [  |   ]  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Enter    |      | Home | PgUp | PgDwn| End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid_wrapper( \
  KC_GESC, KC_EXLM, KC_AT, KC_HASH,    KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
  _______, ____________FUNCTION_3____________, _______, _______, KC_LCBR, KC_RCBR, _______, _______, KC_BSPC, \
  _______, ____________FUNCTION_2____________, _______, _______, KC_LPRN, KC_RPRN, KC_LT,   KC_GT,   _______, \
  _______, ____________FUNCTION_1____________, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_ENT,  KC_ENT,  _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END   \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |Aud on|AudOff|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |MusMod|Mus on|MusOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |Qwerty| Game |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid_wrapper( \
  ____________FUNCTION_1____________, ____________FUNCTION_2____________, ____________FUNCTION_3____________, \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  \
  _______, _______, _______, _______, _______, AU_ON,   AU_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, MU_MOD,  MU_ON,   MU_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,  GAME,    _______, _______  \
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

    case GAME_MOD:
      if (record->event.pressed) {
        layer_on(_GAME_MOD);
      } else {
        layer_off(_GAME_MOD);
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
