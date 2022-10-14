/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "drashna.h"

// Fillers to make layering more clear
#define TT_MDIA TT(_MEDIA)

// enum more_custom_keycodes {
//  KC_P00 = NEW_SAFE_RANGE
//};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_NUMLOCK] = LAYOUT_ortho_5x7(
      KC_NO,   TG_DBLO, TG_GAME, KC_NUM,  KC_SCRL, KC_COLN, KC_PSLS,
      TT_MDIA, KC_CALC, XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PAST,
      KC_HOME, KC_DEL,  KC_PGUP, KC_P4,   KC_P5,   KC_P6,   KC_PMNS,
      KC_END,  KC_UP,   KC_PGDN, KC_P1,   KC_P2,   KC_P3,   KC_PPLS,
      KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_COLN, KC_PENT
  ),

  [_DIABLO] = LAYOUT_ortho_5x7(
      KC_ESC,  _______, KC_V,    KC_D,    XXXXXXX, XXXXXXX, KC_L,
      KC_TAB,  KC_S,    KC_F,    KC_I,    KC_M,    KC_T,    KC_J,
      KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_G,    KC_F,
      KC_LCTL, KC_D3_3, KC_D3_3, KC_D3_3, KC_D3_3, KC_Z,    KC_DIABLO_CLEAR,
      KC_LALT, KC_F4,   KC_F5,   KC_F8,   KC_F9,   KC_F10,  SFT_T(KC_SPACE)
  ),

  [_GAMEPAD] = LAYOUT_ortho_5x7(  // Game pad layout designed primarily for Overwatch
      KC_NO,   KC_ESC,  _______, KC_1,    KC_2,    KC_3,    KC_4,
      TT_MDIA, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
      KC_Z,    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
      KC_Y,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
      KC_F1,   KC_U,    KC_I,    KC_Y,    KC_V,    KC_SPC,  KC_V
  ),

  [_MEDIA] = LAYOUT_ortho_5x7(
      QK_MAKE, QK_BOOT, MU_TOG,  AU_ON,   AU_OFF,  CK_TOGG, RGB_SAD,
      _______, EE_CLR, KC_RGB_T,RGB_M_P, RGB_M_B, RGB_M_R, RGB_SAI,
      RGB_TOG, RGB_MOD, RGB_RMOD,RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_HUD,
      KC_MPLY, KC_MPRV, KC_MNXT, RGB_M_X, RGB_M_G, RGB_M_P, RGB_HUI,
      KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, RGB_VAD, RGB_VAI
  )


};
// clang-format on

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    // switch (keycode) {
    // case KC_P00:
    //  if (!record->event.pressed) {
    //    tap(KC_KP_0);
    //    tap(KC_KP_0);
    //  }
    //  return false;
    //  break;
    //}
    return true;
}

void matrix_init_keymap(void) {
#ifndef CONVERT_TO_PROTON_C
    setPinOutput(D5);
    writePinHigh(D5);

    setPinOutput(B0);
    writePinHigh(B0);
#endif
}
