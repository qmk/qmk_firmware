/*
Copyright 2022 Hector Galindo <hi@hsuchil.com>

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
#include "hsuchil.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BSE] = LAYOUT_moonlander(
        KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS ,KC_EQL  ,KC_BSPC ,
        KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_HOME ,KC_PGUP ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_DEL  ,
        RCT_ESC ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_END  ,KC_PGDN ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
        KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B                      ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_ENT  ,
        KC_LCTL ,KC_HYPR ,KC_LALT ,KC_LGUI ,L_LOW            ,L_LWESC ,LCT_ESC          ,L_HGH   ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,
        KC_SPC  ,KC_LGUI ,KC_RCTL                                                                         ,KC_MEH  ,KC_BSPC ,KC_ENT
    ),

    [_LOW] = LAYOUT_moonlander(
        _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_LCBR ,KC_RCBR ,KC_QUES ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_UNDS ,KC_PLUS ,KC_LCBR ,KC_RCBR ,KC_PIPE ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______                   ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______          ,_______ ,_______          ,_______ ,KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END  ,
        _______ ,_______ ,_______                                                                         ,_______ ,_______ ,_______
    ),

    [_HGH] = LAYOUT_moonlander(
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_LBRC ,KC_RBRC ,KC_SLSH ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_MINS ,KC_EQL  ,KC_LBRC ,KC_RBRC ,KC_BSLS ,
        _______ ,_______ ,_______ ,_______ ,_______ ,_______                   ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______          ,_______ ,_______          ,_______ ,KC_MNXT ,KC_VOLD ,KC_VOLU ,KC_MPLY ,
        _______ ,_______ ,_______                                                                         ,_______ ,_______ ,_______
    ),

    [_FNC] = LAYOUT_moonlander(
        _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,_______ ,
        _______ ,RESET   ,DEBUG   ,_______ ,_______ ,RCG_NRM ,_______ ,_______ ,RCG_SWP ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,RGB_SPD ,RGB_SPI ,_______ ,_______ ,AG_NORM ,_______ ,_______ ,AG_SWAP ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,RGB_TOG ,RGB_MOD ,_______ ,_______ ,_______                   ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______ ,_______ ,_______          ,_______ ,_______          ,_______ ,_______ ,_______ ,_______ ,_______ ,
        _______ ,_______ ,_______                                                                         ,_______ ,_______ ,_______
    )
};
