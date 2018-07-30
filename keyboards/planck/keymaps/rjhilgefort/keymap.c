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
/*
* Example
* ,----------------------------------------------------------------------------------------------------------.
* |       |        |        |        |        |        |        |        |        |        |        |        |
* |-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
* |       |        |        |        |        |        |        |        |        |        |        |        |
* |-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
* |       |        |        |        |        |        |        |        |        |        |        |        |
* |-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
* |       |        |        |        |        |                 |        |        |        |        |        |
* `----------------------------------------------------------------------------------------------------------'
*
[_EXAMPLE] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},
 */

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  EXT_PLV
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define CTRL_ESC MT(MOD_LCTL, KC_ESC)
#define HYPER LCTL(LALT(QK_LGUI))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
* ,-----------------------------------------------------------------------------------------------------.
* | Tab    |    Q   |    W   |   E  |    R   |   T   |   Y   |   U  |    I   |    O   |   P    | Bksp   |
* |--------+--------+--------+------+--------+-------+-------+------+--------+--------+--------+--------|
* | Ct/Esc |    A   |    S   |   D  |    F   |   G   |   H   |   J  |    K   |    L   |   ;    |  "     |
* |--------+--------+--------+------+--------+-------+-------+------+--------+--------+--------+--------|
* | Shift  |    Z   |    X   |   C  |    V   |   B   |   N   |   M  |    ,   |    .   |   /    | Enter  |
* |--------+--------+--------+------+--------+-------+-------+------+--------+--------+--------+--------|
* |        |  Ctrl  |   Alt  | Rais |   GUI  |     Space     | Lowr | Hyper  |        |        | Raise  |
* `-----------------------------------------------------------------------------------------------------'
*/
[_QWERTY] = {
  {KC_TAB,   KC_Q,    KC_W,    KC_E,  KC_R,    KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC},
  {CTRL_ESC, KC_A,    KC_S,    KC_D,  KC_F,    KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT,  KC_Z,    KC_X,    KC_C,  KC_V,    KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {_______,  KC_LCTL, KC_LALT, RAISE, KC_LGUI, KC_SPC, KC_SPC, LOWER, HYPER,   _______, _______, RAISE  }
},

/* Lower
* ,-----------------------------------------------------------------------------------------------------------.
* |       |   \    |   /    |   [    |   ]    |   ~    |   |    |   =    |   +    |    -    |    _   |        |
* |-------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
* |       |   {    |   }    |   (    |   )    |   `    |   ←    |   ↓    |   ↑    |    →    |  Alt   |        |
* |-------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
* |       |   !    |   @    |   #    |   $    |   %    |   ^    |   &    |   *    |    (    |    )   |        |
* |-------+--------+--------+--------+--------+--------+--------+--------+--------+---------+--------+--------|
* |       |        |        |        |        |                 |        |        |         |        |        |
* `-----------------------------------------------------------------------------------------------------------'
*/
[_LOWER] = {
  {_______, KC_BSLS, KC_SLSH, KC_LBRC, KC_RBRC, KC_TILD, KC_PIPE, KC_EQL,  KC_PLUS, KC_MINS,  KC_UNDS, _______},
  {_______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_GRV,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_LALT, _______},
  {_______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______}
},

/* Raise
* ,----------------------------------------------------------------------------------------------------------.
* |       |        |        | Scrn - | Scrn + |        |        |   7    |   8    |   9    |        |        |
* |-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
* |       |        | VolMte | Vol -  | Vol +  |        |        |   4    |   5    |   6    |        |        |
* |-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
* |       |        | Trak ← | Trak → | Ply/Pse|        |        |   1    |   2    |   3    |        |        |
* |-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
* |       |        |        |        |        |                 |   0    |   0    |   .    |        |        |
* `----------------------------------------------------------------------------------------------------------'
*/
[_RAISE] = {
  {_______, _______, _______, KC_SLCK, KC_PAUS, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______},
  {_______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, KC_4,    KC_5,    KC_6,    _______, _______},
  {_______, _______, KC_MRWD, KC_MFFD, KC_MPLY, _______, _______, KC_1,    KC_2,    KC_3,    _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_0,    KC_0,    KC_DOT,  _______, _______}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   _______, _______, _______, _______, _______, _______, _______,  _______, _______, KC_DEL },
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______,  _______, _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______}
}

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
  }
  return true;
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
