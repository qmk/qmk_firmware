/*
Copyright 2021 @Yowkees
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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for development
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     , KC_LBRC  ,           KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_EQL   ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     , KC_RBRC  ,           KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , _______  ,           KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_BSLS  ,
    KC_LCTL  , KC_APP   , MO(1)    , SCRL_MO  ,KC_MS_BTN1, KC_ENT   ,           _______  , KC_SPC   , KC_RALT  , MO(1)    , KC_RGUI  , KC_RSFT
  ),

  [1] = LAYOUT_universal(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,           RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,           RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,           _______  , CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT    , EE_CLR  , _______  , _______  , _______  , _______  ,           _______  , _______  , SCRL_DVD , SCRL_DVI , _______  , KBC_RST
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

void keyboard_post_init_user(void) {
#if defined(DEBUG_PMW3360_SCAN_RATE) && defined(CONSOLE_ENABLE)
    debug_enable = true;
#endif
}
