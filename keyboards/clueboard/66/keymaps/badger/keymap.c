/*
Copyright 2020 Dan White <opensource@bluetufa.com>

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
#include "badger.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY_LINUX]      = LAYOUT_66_ansi(\
      KC_GRV,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,  KC_HOME, \
      KC_TAB,    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,  KC_END, \
      MOVE,      KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   KC_ENT, \
      KC_LSFT,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,   KC_UP,  \
      KC_LCTL,   KC_LALT,  KC_LGUI,  KC_SPC,   ADJUST,   KC_RGUI,  KC_LALT,  KC_LEFT,  KC_DOWN,  KC_RGHT),

  [_MOVE_LINUX]        = LAYOUT_66_ansi(\
     KC_ESC,     VD_1,     VD_2,     VD_3,     KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   IJ_UP,     IJ_DOWN,  KC_DEL,   KC_PGUP, \
     _______,    IJ_STEP,  IJ_INTO,  IJ_OUT,   IJ_RUN,   IJ_STOP,  IJ_OUT,   KC_PGUP,  KC_HOME,  KC_END,   KC_PGDN,  IJ_BACK,   IJ_FWD,   KC_INS,   KC_PGDN, \
     _______,    WM_LH,    WM_UH,    WM_RH,    WD_FRWD,  MAC_POP,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  CS_RIGHT, CS_DOWN,   _______, \
     _______,    MM_UH,    MM_BH,    MAC_CPY,  MAC_PST,  WD_BACK,  KC_MNXT,  IJ_REN,   IJ_IMPL,  IJ_DECL,  IJ_USAG,  _______,   KC_BRIU, \
     _______,    _______,  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_BRID,  KC_END),

  [_QWERTY_MAC]  = LAYOUT_66_ansi(\
      KC_GRV,    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,  KC_HOME, \
      KC_TAB,    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,  KC_END, \
      MOVE_MAC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   KC_ENT, \
      KC_LSFT,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,   KC_UP,  \
      KC_LCTL,   KC_LALT,  KC_LGUI,  KC_SPC,   ADJUST,   KC_RGUI,  KC_LALT,  KC_LEFT,  KC_DOWN,  KC_RGHT),

  [_MOVE_MAC]    = LAYOUT_66_ansi(\
     KC_ESC,     M_VD1,    M_VD2,    M_VD3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   IJ_UP,     IJ_DOWN,  KC_DEL,   KC_PGUP, \
     _______,    IJ_STEP,  IJ_INTO,  IJ_OUT,   IJ_RUN,   IJ_STOP,  IJ_OUT,   KC_PGUP,  KC_HOME,  KC_END,   KC_PGDN,  IJ_BACK,   IJ_FWD,   KC_INS,   KC_PGDN, \
     _______,    MM_LH,    MM_MAX,   MM_RH,    WD_FRWD,  MAC_POP,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  CM_RIGHT, CM_DOWN,   _______, \
     _______,    MM_UH,    MM_BH,    MAC_CPY,  MAC_PST,  WD_BACK,  KC_MNXT,  IJ_REN,   IJ_IMPL,  IJ_DECL,  IJ_USAG,  _______,   KC_BRIU, \
     _______,    _______,  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_BRID,  KC_END),

  [_ADJUST]      = LAYOUT_66_ansi(\
      KC_ESC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL,   KC_VOLU, \
      _______,   NK_ON,    NK_OFF,   EEP_RST,  RESET,     KC_MSTP, KC_MPLY,  KC_PGUP,  KC_HOME,  KC_END,   KC_PGDN,  AG_SWAP,   AG_NORM,  KC_INS,   KC_VOLD, \
      _______,   GE_SWAP,  GE_NORM,  DEBUG,    AG_SWAP,   AG_NORM, KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,   _______, \
      _______,   DF_1,     DF_2,     KC_CAPS,  _______,   KC_MPRV, KC_MNXT,  KC_MUTE,  KC_WBAK,  KC_WFWD,  _______,  _______,   KC_BRIU, \
      _______,   _______,  _______,  _______,  _______,   _______, _______,  KC_HOME,  KC_BRID,  KC_END)
};

