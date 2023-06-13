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
#undef AUDIO_ENABLE

#include "ortho.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY_MAC_ORTHO] = LAYOUT_ortho_4x12(
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC, \
      MOMAC,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT, \
      KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,  \
      J_FUN,    KC_LCTL,  KC_LALT,  KC_LGUI,  RAISE,    KC_SPC,   KC_SPC,   LOWER,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT),

  [_MOVE_MAC_ORTHO]   = LAYOUT_ortho_4x12(
      KC_BACK,  IJ_STEP,  IJ_INTO,  IJ_OUT,   IJ_RUN,   IJ_STOP,  IJ_TOP,   WD_BACK,  KC_HOME,  KC_END,   WD_FRWD,  WD_DELE, \
      _______,  MM_LH,    MM_MAX,   MM_RH,    IJ_FIND,  IJ_LINE,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  CM_RIGHT, _______, \
      _______,  MM_UH,    MM_BH,    MAC_CPY,  MAC_SPS,  SHEBANG,  IJ_BOTT,  IJ_REN,   IJ_IMPL,  IJ_DECL,  IJ_USAG,  _______, \
      _______,  _______,  _______,  _______,  _______,  KC_BSPC,  _______,  _______,  _______,  _______,  _______,  _______),

  [_RAISE]    = LAYOUT_ortho_4x12(
      KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PIPE, \
      _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_DQUO, \
      _______,  KC_F7,    KC_F8,    KC_9,     KC_F10,   KC_F11,   KC_F12,   KC_MUTE,  KC_LT,    KC_GT,    KC_QUES,  _______, \
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______),

  [_LOWER]    = LAYOUT_ortho_4x12(
      KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSLS, \
      _______,  KC_4,     KC_5,     KC_6,     KC_PMNS,  KC_PSCR,  KC_BSLS,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_QUOT, \
      _______,  KC_1,     KC_2,     KC_3,     KC_PPLS,  KC_NO,    KC_NO,    KC_WHOM,  KC_WBAK,  KC_WFWD,  KC_WSCH,  KC_RSFT, \
      _______,  KC_0,     KC_DOT,   KC_ENT,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______),

  [_FUNCTION_ORTHO]   = LAYOUT_ortho_4x12(
      _______,  KC_7,     KC_8,     KC_9,     IJ_RFMT,  KC_MSTP,  KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R,  KC_BTN2,  KC_INS,  \
      _______,  KC_4,     KC_5,     KC_6,     KC_PMNS,  AG_NORM,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_BTN1,  _______, \
      KC_0,     KC_1,     KC_2,     KC_3,     KC_PPLS,  KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_ACL0,  KC_ACL1,  KC_ACL2,  _______, \
      _______,  KC_PDOT,  KC_PEQL,  KC_PSLS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  J_ADJ),

  [_ADJUST_ORTHO]   = LAYOUT_ortho_4x12(
      _______,  NK_ON,    NK_OFF,   EE_CLR,   QK_BOOT,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  \
      _______,  GE_SWAP,  GE_NORM,  DB_TOGG,  AG_SWAP,  AG_NORM,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_BTN1,  _______, \
      _______,  KC_LYRC,  KC_FIRST, KC_CAPS,  KC_NO,    KC_MPRV,  KC_MNXT,  KC_MUTE,  KC_ACL0,  KC_ACL1,  KC_ACL2,  _______, \
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______)
};
