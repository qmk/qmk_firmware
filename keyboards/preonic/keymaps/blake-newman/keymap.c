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

enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  NUMPAD,
  LOWER,
  RAISE,
  BACKLIT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
  * ,-----------------------------------------------------------------------------------.
  * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Bksp |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise |      |  Alt | Ctrl | Shift|
  * `-----------------------------------------------------------------------------------'
  */
  [_QWERTY] = {
    {KC_GRV,  KC_1,    KC_2,    KC_5,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL},
    {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
    {KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT},
    {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   _______, KC_RALT, KC_RCTL, KC_RSFT}
  },

  /* Colemak
  * ,-----------------------------------------------------------------------------------.
  * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Bksp |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise |      |  Alt | Ctrl | Shift|
  * `-----------------------------------------------------------------------------------'
  */
  [_COLEMAK] = {
    {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL},
    {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
    {KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
    {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT},
    {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   _______, KC_RALT, KC_RCTL, KC_RSFT}
  },

  /* Dvorak
  * ,-----------------------------------------------------------------------------------.
  * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Bksp |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise |      |  Alt | Ctrl | Shift|
  * `-----------------------------------------------------------------------------------'
  */
  [_DVORAK] = {
    {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL},
    {KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC},
    {KC_BSPC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH},
    {KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT},
    {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   _______, KC_RALT, KC_RCTL, KC_RSFT}
  },

  /* Numpad
  * ,-----------------------------------------------------------------------------------.
  * | Esc  |      |      | PgDn | PgUp | Home |  End  |      |   /  |   *  |   -  | Del  |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Tab  |      |  Up  |      |      |      |      |   7  |   8  |   9  |   +  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Bksp | Left | Down | Right|      |      |      |   4  |   5  |   6  |      |  "   |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shift|      |      |      |      |      |   ,  |   1  |   2  |   3  |      | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise |   0  |   .  | Ctrl | Shift|
  * `-----------------------------------------------------------------------------------'
  */
  [_NUMPAD] = {
    {KC_ESC,  _______, _______, KC_PGDN, KC_PGUP, KC_END,  KC_HOME, _______, KC_PSLS, KC_PAST, KC_PMNS, KC_DEL},
    {KC_TAB,  _______, KC_UP,   _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_BSPC},
    {KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, KC_QUOT},
    {KC_LSFT, _______, _______, _______, _______, _______, KC_COMM, KC_P1,   KC_P2,   KC_P3,   _______, KC_RSFT},
    {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_P0,   KC_PDOT, KC_RCTL, KC_RSFT}
  },


  /* Lower
  * ,-----------------------------------------------------------------------------------.
  * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * |  Esc |      |  Up  |      |      |      |      |   -_ |   -  |   +  |   =  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * |  Bksp| Left | Down | Right|      |      |      |   {  |   }  |   [  |   ]  |   \  |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shift|   |  |      |      |      |      |      |      |      |   ¢  |   €  | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Brite| Ctrl | Alt  | GUI  |Lower |    Enter    |Raise |      |  Alt | Ctrl | Shift|
  * `-----------------------------------------------------------------------------------'
  */
  [_LOWER] = {
    {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
    {KC_ESC,  _______, KC_UP,   _______, _______, _______, _______, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  KC_BSPC},
    {KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_BSLS},
    {KC_LSFT, KC_PIPE, _______, _______, _______, _______, _______, _______, ALGR_T(KC_4), ALGR_T(KC_5), _______,  KC_RSFT},
    {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_ENT,  KC_ENT,  RAISE,   _______, KC_RALT, KC_RCTL, KC_RSFT}
  },

  /* Raise
  * ,-----------------------------------------------------------------------------------.
  * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * |  Esc |      |  Up  |      |      |      |      |   -  |   _  |   =  |   +  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Bksp | Left | Down | Right|      |      |      |   [  |  ]   |   {  |   }  |   |  |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shift|  \   |      |      |      |      |      |      |      |   £  |  $   | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Brite| Ctrl | Alt  | GUI  |Lower |    Enter    |Raise |      |  Alt | Ctrl | Shift|
  * `-----------------------------------------------------------------------------------'
  */
  [_RAISE] = {
    {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
    {KC_ESC,  _______, KC_UP,   _______, _______, _______, _______, KC_MINS, KC_UNDS, KC_EQL,  KC_PLUS, KC_BSPC},
    {KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_PIPE},
    {KC_LSFT, KC_BSLS, _______, _______, _______, _______, _______, _______, _______, ALGR_T(KC_DLR), KC_DLR,  KC_RSFT},
    {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_ENT,  KC_ENT,  RAISE,   _______, KC_RALT, KC_RCTL, KC_RSFT}
  },

  /* Adjust (Lower + Raise)
  * ,-----------------------------------------------------------------------------------.
  * |      |      |      |      |      |      |      |      |      |      |      |      |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      | Reset| Debug|      |      |      |      |      |      | aPscr| sPscr| Pscr |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Caps |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Numpad|Insert|
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
  * `-----------------------------------------------------------------------------------'
  */
  [_ADJUST] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,LALT(KC_PSCR), LCTL(KC_PSCR), KC_PSCR},
    {KC_CAPS, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  NUMPAD,  KC_INS},
    {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
  }

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
        case NUMPAD:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_NUMPAD);
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
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            PORTE &= ~(1<<6);
          } else {
            unregister_code(KC_RSFT);
            PORTE |= (1<<6);
          }
          return false;
          break;
      }
    return true;
};
