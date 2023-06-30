/*
Copyright 2021 Chuck "@vosechu" Lauer Vose <vosechu@gmail.com>

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

#include "vosechu.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DV] = LAYOUT(
    PAWFIVE , KC_QUOT , KC_COMM , KC_DOT  , KC_P    , KC_Y    , KC_F    , KC_G    , KC_C    , KC_R    , KC_L    , QK_BOOT,
    KC_ESC  , KC_A    , KC_O    , KC_E    , LWR_U   , KC_I    , KC_D    , RSE_H   , KC_T    , KC_N    , KC_S    , XXXXXXX ,
    XXXXXXX , KC_SCLN , KC_Q    , KC_J    , KC_K    , KC_X    , KC_B    , KC_M    , KC_W    , KC_V    , KC_Z    , KC_ENT  ,
    XXXXXXX , CTL_GRV , ALT_TAB , KC_LGUI , LFT_BK  , SFT_SPC , KC_SPC  , LFT_ENT , KC_MINS , KC_EQL  , KC_SLSH , KC_BSLS
  ),
  [QW] = LAYOUT(
    KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
    KC_ESC  , KC_A    , KC_S    , KC_D    , LWR_F   , KC_G    , KC_H    , RSE_J   , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,
    KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_ENT  ,
    KC_HYPR , CTL_GRV , ALT_TAB , KC_LGUI , LFT_BK  , SFT_SPC , KC_SPC  , LFT_ENT , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT
  ),
  [LWR] = LAYOUT(
    _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_7    , KC_8    , KC_9    , XXXXXXX , _______ ,
    _______ , XXXXXXX , XXXXXXX , XXXXXXX , _LAYER_ , XXXXXXX , XXXXXXX , KC_4    , KC_5    , KC_6    , XXXXXXX , _______ ,
    _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_1    , KC_2    , KC_3    , XXXXXXX , _______ ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_0    , KC_0    , KC_DOT  , _______ , _______
  ),
  [RSE] = LAYOUT(
    _______ , KC_LABK , KC_RABK , KC_LCBR , KC_RCBR , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,
    _______ , KC_LPRN , KC_RPRN , KC_LBRC , KC_RBRC , XXXXXXX , XXXXXXX , _LAYER_ , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,
    _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),
  [LFT] = LAYOUT(
    _______ , BWSR_BK , TAB_LFT , KC_UP   , TAB_RGT , BWSR_FW , KC_MUTE , XXXXXXX , SCR_LFT , SCR_FUL , SCR_RGT , _______ ,
    _______ , XXXXXXX , KC_LEFT , KC_DOWN , KC_RGHT , KC_PGUP , KC_VOLU , SLACKUP , XXXXXXX , XXXXXXX , TO(QW)  , _______ ,
    _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_PGDN , KC_VOLD , SLACKDN , XXXXXXX , XXXXXXX , TO(DV)  , _______ ,
    _______ , QK_BOOT, _______ , _______ , _LAYER_ , KC_BSPC , _______ , KC_LSFT , KC_LGUI , KC_LALT , KC_LCTL , _______
  )
};
