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
  [_QWERTY_MAC] = LAYOUT_60_ansi(\
     KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC, \
     KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS, \
     MOVE_MAC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   KC_ENT,   \
     KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,   \
     KC_LCTL,    KC_LALT,  KC_LGUI,  KC_SPC,   ADJUST,   KC_RGUI,  KC_RALT,  MAC_POP),

  [_MOVE_MAC]   = LAYOUT_60_ansi(\
     MAC_FRC,    MM_LEFT,  MM_RGHT,  KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_0,     IJ_TOP,    IJ_BOTT,  KC_DEL, \
     KC_BACK,    IJ_STEP,  IJ_INTO,  IJ_OUT,   IJ_RUN,   IJ_STOP,  _______,  WD_BACK,  KC_HOME,  KC_END,   WD_FRWD,  IJ_BACK,   IJ_FWD,   KC_NEXT, \
     _______,    MM_LH,    MM_MAX,   MM_RH,    IJ_FIND,  IJ_IMPS,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  CM_RIGHT, CM_DOWN,   _______,  \
     _______,    MM_UH,    MM_BH,    MAC_CPY,  MAC_PST,  IJ_IMPH,  _______,  IJ_REN,   IJ_IMPL,  IJ_DECL,  IJ_USAG,  _______,   \
     _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______),
     
  [_QWERTY_LINUX] = LAYOUT_60_ansi(\
     KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC, \
     KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS, \
     MOVE,       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   KC_ENT,   \
     KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,   \
     KC_LCTL,    KC_LGUI,  KC_LALT,  KC_SPC,   ADJUST,   KC_LALT,  KC_RGUI,  KC_RCTL),

  [_MOVE_LINUX] = LAYOUT_60_ansi(\
     KC_GRV,     VD_1,     VD_2,     VD_3,     KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL, \
     KC_BACK,    WM_VD1,   WM_UH,    WM_VD2,   RESET,    KC_MSTP,  KC_MPLY,  KC_PGUP,  KC_HOME,  KC_END,   KC_PGDN,  _______,   _______,  KC_NEXT, \
     _______,    WM_LH,    WM_MAX,   WM_RH,    WD_FRWD,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  CS_RIGHT, CS_DOWN,   _______, \
     _______,    WM_VD3,   WM_BH,    OS_COPY,  OS_PAST,  WD_BACK,  KC_MNXT,  KC_MUTE,  KC_WBAK,  KC_WFWD,  _______,  _______,   \
     _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______),

  [_ADJUST]     = LAYOUT_60_ansi(\
     KC_ESC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL, \
     _______,   _______,  _______,  _______,  KC_WREF,   KC_MSTP,  KC_MPLY,  KC_PGUP,  _______,  _______,  KC_PGDN,  KC_VOLD,   KC_VOLU,  KC_INS, \
     _______,   _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  \
     _______,   DF_1,     DF_2,     KC_CAPS,  _______,   KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_WBAK,  KC_WFWD,  KC_WSCH,  _______,   \
     _______,   _______,  _______,  _______,  _______,   _______,  _______,  MO(_CONFIG)),

  [_CONFIG]     = LAYOUT_60_ansi(\
     _______,   KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL, \
     _______,   NK_ON,    NK_OFF,   EEP_RST,  RESET,     _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  KC_INS, \
     _______,   GE_SWAP,  GE_NORM,  DEBUG,    RGB_MOD,   RGB_HUI,  RGB_SAI,  RGB_SPI,  RGB_M_B,  _______,  _______,  RGB_TOG,   _______,  \
     _______,   LAG_SWP,  LAG_NRM,  _______,  RGB_RMOD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  RGB_M_K,  _______,  _______,  _______,   \
     _______,   _______,  _______,  _______,  _______,   _______,  _______,  _______)
};

