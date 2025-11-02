/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // keymap for development
    [0] = LAYOUT_no_ball(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        KC_LCTL, KC_LGUI, KC_LALT, SCRL_MO, KC_SPC,  LT(1,KC_TAB),      LT(1,KC_BSPC), KC_ENT,  SCRL_MO, KC_RALT, KC_RGUI, KC_RSFT
    ),

    [1] = LAYOUT_no_ball(
        RGB_TOG,  _______, _______, _______, _______,                         RGB_M_P, RGB_M_B,  RGB_M_R,  RGB_M_SW, RGB_M_SN,
        RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, SCRL_DVI,                        RGB_M_K, RGB_M_X,  RGB_M_G,  RGB_M_T,  RGB_M_TW,
        RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, SCRL_DVD,                        CPI_D1K, CPI_D100, CPI_I100, CPI_I1K,  KBC_SAVE,
        QK_BOOT,  KBC_RST, _______, _______, _______,  _______,      _______, _______, _______,  _______,  KBC_RST,  QK_BOOT
    ),
};
// clang-format on

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
