/* Copyright 2021 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
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

#include QMK_KEYBOARD_H

#define LSA_DEL LSA_T(KC_DEL)
#define RALTHOM RALT_T(KC_HOME)
#define RWINEND RGUI_T(KC_END)
#define RCTLEND RCTL_T(KC_END)
#define LSHNUBS LSFT_T(KC_NUBS)
#define RSHF_RO RSFT_T(KC_INT1)
#define FN_CALC LT(1,KC_CALC)
#define FN_MENU LT(1,KC_MENU)
#define FN_PENT LT(1,KC_PENT)
#define CTALDEL LCA(KC_DEL)
#define JPYEN   KC_INT3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_rh(

KC_ESC ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,                KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_HOME,KC_END ,KC_PGUP,KC_PGDN,KC_DEL ,KC_INS ,KC_PSCR,KC_BSPC,    
        KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,                KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,KC_EQL ,KC_BSPC,KC_BSPC,        KC_EQL ,KC_PSLS,KC_PAST,KC_PMNS,    
        KC_TAB ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,                KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,KC_RBRC,KC_BSLS,                KC_P7  ,KC_P8  ,KC_P9  ,KC_PPLS,     
        KC_LCTL,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,                KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,KC_ENT ,KC_ENT ,                KC_P4  ,KC_P5  ,KC_P6  ,KC_PPLS,     
KC_LSFT,KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,LSA_DEL,FN_CALC,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,KC_RSFT,KC_UP  ,                KC_P1  ,KC_P2  ,KC_P3  ,FN_PENT,     
        KC_LCTL,KC_LGUI,        KC_LALT,FN_MENU,KC_SPC ,                RALTHOM,        RALTHOM,        RWINEND,RCTLEND,KC_LEFT,KC_DOWN,KC_RGHT,        KC_P0  ,KC_P0  ,KC_PDOT,FN_PENT),   
    
    
[1] = LAYOUT_rh(
QK_BOOT,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_F13 ,KC_F14 ,KC_F15 ,KC_F16 ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,    
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,        KC_NUM ,XXXXXXX,XXXXXXX,XXXXXXX,    
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,QK_BOOT,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,JPYEN  ,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,     
        KC_CAPS,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,KC_SCRL,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,     
LSHNUBS,LSHNUBS,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_BRK ,CTALDEL,_______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,RSHF_RO,RSHF_RO,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,_______,     
        _______,_______,        _______,_______,XXXXXXX,                _______,        _______,        _______,_______,XXXXXXX,XXXXXXX,XXXXXXX,        XXXXXXX,XXXXXXX,KC_PCMM,_______)
};
