/* Copyright 2020 Yoonbae Cho
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
 * Refereces:
 * https://beta.docs.qmk.fm/using-qmk/guides/keymap
 * https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes
 * https://beta.docs.qmk.fm/using-qmk/software-features/feature_layers
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/keebio/iris/keymaps/dbroqua/keymap.c
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/keebio/iris/keymaps/fluffactually/keymap.c
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/keebio/iris/keymaps/dcompact/keymap.c
 * https://github.com/qmk/qmk_firmware/blob/master/keyboards/planck/keymaps/smittey/keymap.c
 */


#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

#define KC_ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
    /*
     * ,-----+-----+-----+-----+-----+-----+                ,-----+-----+-----+-----+-----+-----+
     * |~ESC~|  1  |  2  |  3  |  4  |  5  |                |  6  |  7  |  8  |  9  |  0  |  `  |
     * |-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * | TAB |  Q  |  W  |  E  |  R  |  T  |                |  Y  |  U  |  I  |  O  |  P  | BSLS|
     * +-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * | LCTL|  A  |  S  |  D  |  F  |  G  |                |  H  |  J  |  K  |  L  |  ;  |  '  |
     * +-----+-----+-----+-----+-----+-----+-----.    ,-----+-----+-----+-----+-----+-----+-----+
     * | LSFT|  Z  |  X  |  C  |  V  |  B  |TT(2)/    \     |  N  |  M  |  ,  |  .  |  /  | BSPC|
     * +-----+-----+-----+--+--+-----+-----+----/      \ SPC+-----+-----+--+--+-----+-----+-----+
     *                      \ LGUI| LALT| TT(1)/        \      | ENT | HAEN/
     *                      `-----+-----+-----'          `-----+-----+----'
     */
     GESC,  1  ,  2  ,  3  ,  4  ,  5  ,                 6  ,  7  ,  8  ,  9  ,  0  ,  GRV, 
     TAB ,  Q  ,  W  ,  E  ,  R  ,  T  ,                 Y  ,  U  ,  I  ,  O  ,  P  , BSLS, 
     LCTL,  A  ,  S  ,  D  ,  F  ,  G  ,                 H  ,  J  ,  K  ,  L  , SCLN, QUOT, 
     LSFT,  Z  ,  X  ,  C  ,  V  ,  B  , TT(2),   SPC ,  N  ,  M  , COMM, DOT , SLSH, BSPC, 
                          LGUI,  LALT, TT(1),        SPC , ENT , HAEN
  ),

  [_LOWER] = LAYOUT_kc(
    /*
     * ,-----+-----+-----+-----+-----+-----+                ,-----+-----+-----+-----+-----+-----+
     * | F1  | F2  | F3  | F4  | F5  | F6  |                | F7  | F8  | F9  | F10 | F11 | F12 |
     * |-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * |     | PGUP| UP  | PGDN|  (  |  )  |                | HOME| PGDN| PGUP| END |  -  |  =  |
     * +-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * |     | LEFT| DOWN| RGHT|  {  |  }  |                | LEFT| DOWN| UP  | RGHT| NO  | NO  |
     * +-----+-----+-----+-----+-----+-----+-----.    ,-----+-----+-----+-----+-----+-----+-----+
     * |     | NO  | NO  | NO  |  [  |  ]  |     /    \     | NO  | NO  | NO  | NO  | INS | DEL |
     * +-----+-----+-----+--+--+-----+-----+----/      \    +-----+-----+--+--+-----+-----+-----+
     *                      \     |     |      /        \      |     | HANJ/
     *                      `-----+-----+-----'          `-----+-----+----'
     */
     F1   , F2  , F3  , F4  , F5  , F6  ,                F7  , F8  , F9  , F10 , F11 , F12 ,
          , PGUP, UP  , PGDN, LPRN, RPRN,                HOME, PGDN, PGUP, END , MINS, EQL ,
          , LEFT, DOWN, RGHT, LCBR, RCBR,                LEFT, DOWN,   UP, RGHT,   NO,   NO,
          , NO  , NO  , NO  , LBRC, RBRC,    ,        ,    NO,   NO,   NO,   NO,  INS,  DEL, 
                                ,     ,     ,             ,     , HANJ
  ),

  [_RAISE] = LAYOUT_kc(
    /*
     * ,-----+-----+-----+-----+-----+-----+                ,-----+-----+-----+-----+-----+-----+
     * | Prev| Stop| Pla | NO  | NO  | NO  |                | NO  | NO  | P/  | P*  | P-  | Next|
     * |-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * |     | PGUP| UP  | PGDN|     |     |                | NO  |  7  |  8  |  9  | P+  | Vol-|
     * +-----+-----+-----+-----+-----+-----+                +-----+-----+-----+-----+-----+-----+
     * | HOME| LEFT| DOWN| RGHT| END | NO  |                | NO  |  4  |  5  |  6  | ENT | Vol+|
     * +-----+-----+-----+-----+-----+-----+-----.    ,-----+-----+-----+-----+-----+-----+-----+
     * | NO  | PSCR| SLCK| PAUS| NO  | NO  |     /    \     | P=  |  1  |  2  |  3  | ENT | Mute|
     * +-----+-----+-----+--+--+-----+-----+    /      \    +-----+-----+--+--+-----+-----+-----+
     *                      \     |     | TT(0)/        \      |  0  |  .  /
     *                      `-----+-----+-----'          `-----+-----+----'
     */
     MPRV, MSTP, MPLY,  NO ,  NO ,  NO ,                NO , NO  , PSLS, PAST, PMNS, MNXT,
     NO  , PGUP,  UP , PGDN,     ,     ,                NO ,   7 ,   8 ,   9 , PPLS, VOLU,
     HOME, LEFT, DOWN, RGHT,  END,  NO ,                NO ,   4 ,   5 ,   6 ,  ENT, VOLD,
     NO  , PSCR, SLCK, PAUS,  NO ,  NO ,    ,        , PEQL,   1 ,   2 ,   3 ,  ENT, MUTE,
                               ,     ,TT(0),             ,   0 , DOT
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _QWERTY);
      }
      return false;
      break;
  }
  return true;
}