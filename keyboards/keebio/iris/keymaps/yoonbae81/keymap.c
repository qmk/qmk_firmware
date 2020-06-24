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
     GESC,  1  ,  2  ,  3  ,  4  ,  5  ,                 6  ,  7  ,  8  ,  9  ,  0  ,  GRV, 
     TAB ,  Q  ,  W  ,  E  ,  R  ,  T  ,                 Y  ,  U  ,  I  ,  O  ,  P  , BSLS, 
     LCTL,  A  ,  S  ,  D  ,  F  ,  G  ,                 H  ,  J  ,  K  ,  L  , SCLN, QUOT, 
     LSFT,  Z  ,  X  ,  C  ,  V  ,  B  ,TT(_LOWER),SPC,  N  ,  M  , COMM, DOT , SLSH, BSPC, 
                      TT(_RAISE), LGUI, LALT,        SPC , LT(1,KC_HAEN), L(2,KC_HANJ)
  ),

  [_LOWER] = LAYOUT_kc(
     F1   , F2  , F3  , F4  , F5  , F6  ,                F7  , F8  , F9  , F10 , F11 , F12 ,
          , PGUP, UP  , PGDN, LPRN, RPRN,                PSTE, HOME, PGUP,   NO, MINS, EQL ,
          , LEFT, DOWN, RGHT, LCBR, RCBR,                LEFT, DOWN,   UP, RGHT,   NO,   NO,
          , NO  , NO  , NO  , LBRC, RBRC,    ,      ENT, COPY, PGDN,  END,   NO,  INS,  DEL, 
                                ,     , SPC,          ENT,     , 
  ),

  [_RAISE] = LAYOUT_kc(
     MPRV, MSTP, MPLY, MNXT, VOLD, VOLU,                 UNDO, CALC, PSLS, PAST, PMNS, PSCR,
         , PGUP,  UP , PGDN,   NO, MUTE,                 PSTE,   7 ,   8 ,   9 , PPLS, SCLK,
         , LEFT, DOWN, RGHT,   NO,   NO,                  CUT,   4 ,   5 ,   6 , PCMM, PAUS,
         , HOME,   NO,  END,   NO,   NO,TO(_QWERTY),ENT, COPY,   1 ,   2 ,   3 , PEQL, BSPC,
                               ,     , SPC,           ENT,   0 , PDOT
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