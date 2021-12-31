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
  [_QWERTY]  = LAYOUT_tsangan(\
     KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_PIPE, KC_BSLS, \
     KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSPC, \
     MOVE_MAC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,   KC_ENT,   \
     KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,   J_MACRO,  \
     KC_LCTL,    KC_LALT,  KC_LGUI,  KC_SPC,   FUNCTION, KC_RALT,  KC_RGUI),

  [_MOVE]    = LAYOUT_tsangan(\
     MAC_FRC,    MM_LEFT,  MM_RGHT,  KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_0,     IJ_TOP,    IJ_BOTT,  KC_DEL,  KC_BSPC, \
     KC_BACK,    VS_STEP,  VS_INTO,  VS_OUT,   VS_RUN,   VS_STOP,  VS_MVUP,  WD_BACK,  KC_HOME,  KC_END,   WD_FRWD,  IJ_BACK,   IJ_FWD,   WD_DELE, \
     _______,    MM_LH,    MM_MAX,   MM_RH,    IJ_FIND,  VS_LINE,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  CM_RIGHT, CM_DOWN,   _______,  \
     _______,    MM_UH,    MM_BH,    MAC_CPY,  MAC_PST,  _______,  VS_MVDN,  IJ_REN,   IJ_IMPL,  IJ_DECL,  IJ_USAG,  _______,   _______,  \
     _______,    _______,  _______,  _______,  _______,  _______,  _______),

  [_FUNCTION] = LAYOUT_tsangan(\
     KC_ESC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   _______, _______, \
     _______,   VS_EXP,   VS_DBG,   VS_CMD,   VS_FILE,   VS_TERM,  KC_MPLY,  KC_PGUP,  _______,  _______,  KC_PGDN,  KC_VOLD,   KC_VOLU,  KC_INS, \
     _______,   _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  \
     _______,   _______,  _______,  KC_CAPS,  _______,   KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_WBAK,  KC_WFWD,  KC_WSCH,  _______,   _______,  \
     _______,   _______,  _______,  _______,  _______,   _______,  CONFIG),

  [_MACRO]     = LAYOUT_tsangan(\
     SHRUG,     DF_1,     DF_2,     KC_F3,    KC_F4,     KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL,  KC_DEL, \
     SHRUG,     _______,  _______,  _______,  SED,       KC_MSTP,  KC_MPLY,  KC_PGUP,  _______,  _______,  KC_PGDN,  KC_VOLD,   KC_VOLU,  KC_INS, \
     _______,   _______,  SELECT,   _______,  FN,        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  \
     _______,   DF_1,     DF_2,     CONST,    _______,   KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_WBAK,  KC_WFWD,  KC_WSCH,  _______,   _______,  \
     _______,   _______,  _______,  _______,  _______,   _______,  CONFIG),

  [_CONFIG]     = LAYOUT_tsangan(\
     _______,   DF_1,     DF_2,     DF_3,     DF_4,      _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______, _______, \
     _______,   NK_ON,    NK_OFF,   EEP_RST,  RESET,     _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  KC_INS, \
     _______,   GE_SWAP,  GE_NORM,  DEBUG,    RGB_MOD,   RGB_HUI,  RGB_SAI,  RGB_SPI,  RGB_M_B,  _______,  _______,  RGB_TOG,   _______,  \
     _______,   _______,  _______,  _______,  RGB_RMOD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  RGB_M_K,  _______,  _______,  _______,   _______,  \
     _______,   _______,  _______,  _______,  _______,   _______,  _______)
};
