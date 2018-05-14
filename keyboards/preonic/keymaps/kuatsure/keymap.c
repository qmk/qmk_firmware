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

#include "preonic.h"
#include "action_layer.h"
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
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Leader| Game | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  { KC_ESC,  KC_1, KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_TAB,  KC_Q, KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS },
  { KC_LCTL, KC_A, KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
  { KC_LSFT, KC_Z, KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT  },
  { KC_LEAD, GAME, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT },
},

/* Game
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Leader|Qwerty| Alt  |  Spc |Game+ |    Space    |Game+ | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = {
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,    KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    KC_Y,    KC_U,     KC_I,    KC_O,    KC_P,    KC_BSLS },
  { KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    KC_H,    KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    KC_N,    KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_ENT  },
  { KC_LEAD, QWERTY,  KC_LALT, KC_SPC,  GAME_MOD, KC_SPC,  KC_SPC,  GAME_MOD, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT },
},

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
[_GAME_MOD] = {
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
  { _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_GRV,  _______, KC_7,    KC_8,    KC_9,    _______, _______ },
  { _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_TILD, _______, KC_4,    KC_5,    KC_6,    _______, _______ },
  { KC_LSFT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_1,    KC_2,    KC_3,    _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_0,    _______, _______ },
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   <  |   >  |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |  Up  |      |   `  |      |   {  |   }  |  _   |      |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Del  | Left | Down | Right|   ~  |   =  |   (  |   )  |  +   |  :   |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Vol- | Prev | Play | Next | Vol+ |   -  |   [  |   ]  |      |  ?   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Mute |      |      |      |     Esc     |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  { KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC, KC_CIRC, KC_LT,   KC_GT,   _______, _______, _______ },
  { _______, _______, _______, KC_UP,   _______,  KC_GRV,  _______, KC_LCBR, KC_RCBR, KC_UNDS, _______, KC_PIPE },
  { _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_TILD, KC_EQL,  KC_LPRN, KC_RPRN, KC_PLUS, KC_COLN, KC_DQT  },
  { _______, KC_VOLD, KC_MRWD, KC_MPLY, KC_MFFD,  KC_VOLU, KC_MINS, KC_LBRC, KC_RBRC, _______, KC_QUES, _______ },
  { _______, KC_MUTE, _______, _______, _______,  KC_ESC,  KC_ESC,  _______, _______, _______, _______, _______ },
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | E`~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Enter    |      |      | PgUp | PgDwn|      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  { KC_GESC, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______ },
  { _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, KC_BSPC },
  { _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, _______, _______ },
  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, KC_ENT,  KC_ENT,  _______, _______, KC_PGUP, KC_PGDN, _______ },
},

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
[_ADJUST] = {
  { KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12  },
  { _______, RESET,   DEBUG,   _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL  },
  { _______, _______, _______, _______, _______, AU_ON,   AU_OFF,  _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, MU_MOD,  MU_ON,   MU_OFF,  _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,  GAME,    _______, _______ },
},

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
