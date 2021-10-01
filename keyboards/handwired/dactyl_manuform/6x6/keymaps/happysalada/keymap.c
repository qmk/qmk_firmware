/*
Copyright 2021 Raphael Megzari <raphael@megzari.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum custom_layers {
 _COLEMAK_DH,
 _LEFT,
 _LEFT_UP,
 _RIGHT,
 _RIGHT_UP,
 _QWERTY
};

#define COLMAK TO(_COLEMAK_DH)
#define QWERTY TO(_QWERTY)

enum custom_keycodes {
  EQ_SUP = SAFE_RANGE,
  INF_EQ,
  SUP_EQ,
  INF_MIN,
  MIN_SUP,
  PIPE_R,
  SUP_SUP,
  INF_INF,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK_DH] = LAYOUT_6x6(

     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     QWERTY ,KC_Q   ,KC_W   ,KC_F   ,KC_P   ,KC_K   ,                         KC_Z   ,KC_L   ,KC_U   ,KC_Y   ,KC_COLN,_______,
     _______,KC_A   ,KC_R   ,KC_S   ,KC_T   ,KC_G   ,                         KC_M   ,KC_N   ,KC_E   ,KC_I   ,KC_O   ,_______,
     KC_LSFT,KC_J   ,KC_B   ,KC_C   ,KC_D   ,KC_V   ,                         KC_X   ,KC_H   ,KC_COMM,KC_DOT ,KC_QUES,KC_RSFT,
                     KC_K   ,KC_V   ,                                                         KC_X   ,KC_Z   ,
                     LT(_RIGHT_UP,KC_BSPC),LSFT_T(KC_ESC),            LT(_LEFT, KC_ENT),LT(_LEFT_UP,KC_SPC),
                                   _______,LCTL_T(KC_DEL),               LGUI_T(KC_TAB),_______,
                                             _______,_______,         _______,_______
  ),

  [_QWERTY] = LAYOUT_6x6(

     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     COLMAK ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,                         KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,_______,
     _______,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,                         KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_COLN,_______,
     KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,                         KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_QUES,KC_RSFT,
                     _______,_______,                                                         _______,_______,
                     LT(_RIGHT_UP,KC_BSPC),LSFT_T(KC_ESC),            LT(_LEFT, KC_ENT),LT(_LEFT_UP,KC_SPC),
                                   _______,LCTL_T(KC_DEL),               LGUI_T(KC_TAB),_______,
                                             _______,_______,         _______,_______
  ),

  [_LEFT] = LAYOUT_6x6(

     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     _______,_______,KC_PLUS,KC_CIRC,KC_AMPR,_______,                         _______,KC_EQL ,KC_PERC,KC_HASH,_______,_______,
     _______,_______,KC_TILD,KC_DQUO,KC_PIPE,_______,                         _______,KC_LPRN,KC_LCBR,KC_LBRC,_______,_______,
     _______,_______,KC_BSLS,KC_ASTR,KC_SLSH,_______,                         _______,KC_RPRN,KC_RCBR,KC_RBRC,_______,_______,
                     _______,_______,                                                         _______,_______,
                                     _______,_______,                         _______,_______,
                                             _______,_______,         _______,_______,
                                             _______,_______,         _______,_______
  ),

  [_LEFT_UP] = LAYOUT_6x6(

     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     _______,_______,KC_LABK,KC_MINS,KC_RABK,_______,                         _______,KC_7   ,KC_8   ,KC_9   ,_______,_______,
     _______,_______,KC_UNDS,KC_QUOT,KC_DLR ,KC_GRV ,                         _______,KC_4   ,KC_5   ,KC_6   ,KC_0   ,_______,
     _______,_______,KC_SCLN,KC_AT  ,KC_EXLM,_______,                         _______,KC_1   ,KC_2   ,KC_3   ,_______,_______,
                     _______,_______,                                                         _______,_______,
                                     _______,_______,                         _______,_______,
                                             _______,_______,         _______,_______,
                                             _______,_______,         _______,_______
  ),

  [_RIGHT] = LAYOUT_6x6(

     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                         _______,_______,_______,_______,_______,_______,
                     _______,_______,                                                         _______,_______,
                                     _______,_______,                         _______,_______,
                                             _______,_______,         _______,_______,
                                             _______,_______,         _______,_______
  ),

  [_RIGHT_UP] = LAYOUT_6x6(

     _______,_______,_______,_______,_______,_______,                         _______,_______      ,_______    ,_______      ,_______,_______,
     _______,_______,_______,_______,_______,_______,                         _______,_______      ,_______    ,_______      ,_______,_______,
     _______,_______,INF_INF,_______,SUP_SUP,_______,                         _______,LCTL(KC_LEFT),KC_UP      ,LCTL(KC_RGHT),_______,_______,
     _______,_______,MIN_SUP,EQ_SUP ,PIPE_R ,_______,                         _______,KC_LEFT      ,KC_DOWN    ,KC_RGHT      ,LGUI(KC_UP),_______,
     _______,_______,INF_MIN,INF_EQ ,_______,_______,                         _______,_______      ,KC_CAPSLOCK,_______      ,_______,_______,
                     _______,_______,                                                               _______    ,_______      ,
                                     _______,_______,                         _______,_______,
                                             _______,_______,         _______,_______,
                                             _______,_______,         _______,_______
  ),


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case PIPE_R:
      if (record->event.pressed) {
        SEND_STRING("|> ");
      }
      break;
    case EQ_SUP:
      if (record->event.pressed) {
        SEND_STRING("=> ");
      }
      break;
    case INF_EQ:
      if (record->event.pressed) {
        SEND_STRING("<= ");
      }
      break;
    case MIN_SUP:
      if (record->event.pressed) {
        SEND_STRING("-> ");
      }
      break;
    case INF_MIN:
      if (record->event.pressed) {
        SEND_STRING("<- ");
      }
      break;
    case INF_INF:
      if (record->event.pressed) {
        SEND_STRING("<<");
      }
      break;
    case SUP_SUP:
      if (record->event.pressed) {
        SEND_STRING(">>");
      }
      break;
  }
  return true;
}


