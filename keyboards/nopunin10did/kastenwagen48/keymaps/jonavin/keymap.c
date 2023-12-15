/* Copyright 2021 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
 * Copyright 2022 Jonavin Eng, @Jonavin
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
#include "jonavin.h"

#define L2_SPC      LT(2,KC_SPC)
#define L3_SPC      LT(3,KC_SPC)
#define RWINALT     RALT_T(KC_RGUI)
#define ISO_LT      KC_NUBS
#define ISO_GT      LSFT(KC_NUBS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_48(

    KC_TAB      ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,KC_BSPC  , KC_DEL ,
    TT(_RAISE)  ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,KC_ENT   , KC_PGUP,
    KC_LSFTCAPS ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH, SC_SENT ,KC_UP , KC_PGDN,
    KC_LCTL  ,KC_LALT  ,KC_LGUI ,KC_SPC       ,L3_SPC           ,MO(_LOWER) ,MO(_FN1) ,KC_RCTL   ,KC_LEFT,KC_DOWN,KC_RGHT
    ),
[_FN1] = LAYOUT_48(
    KC_GRV  ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_RBRC,KC_DEL       , KC_INS ,
    KC_CAPS ,KC_F11 ,KC_F12 ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_PSCR, KC_SCRL, KC_PAUS,XXXXXXX,XXXXXXX,XXXXXXX    , KC_HOME,
    _______ ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_NUM  ,XXXXXXX ,XXXXXXX,XXXXXXX,XXXXXXX,_______ ,KC_PGUP,    KC_END ,
    _______  ,_______  ,KC_WINLCK,XXXXXXX              ,XXXXXXX          ,_______,_______  ,_______ ,KC_HOME,KC_PGDN,KC_END
    ),
[_LOWER] = LAYOUT_48(
    KC_TILD  ,KC_EXLM, KC_AT, KC_HASH,KC_DLR,KC_PERC,KC_CIRC, KC_AMPR, KC_ASTR,KC_LPRN, KC_RPRN,KC_MINS,KC_EQL     , QK_BOOT,
    _______  ,KC_MINS, KC_EQL,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_QUES,KC_SLSH,KC_PIPE,KC_BSLS,KC_TILD,  XXXXXXX   ,XXXXXXX,
    _______  ,KC_UNDS, KC_PLUS,XXXXXXX,KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC,KC_LT,KC_GT, XXXXXXX ,_______ ,XXXXXXX,XXXXXXX,
    _______  ,_______  ,_______,XXXXXXX              ,XXXXXXX          ,_______,_______  ,_______ ,XXXXXXX,XXXXXXX,XXXXXXX
    ),
[_RAISE] = LAYOUT_48(
 	KC_ESC, KC_HOME,KC_UP,  KC_END, KC_PGUP,KC_PMNS,KC_PPLS,KC_P7,  KC_P8,  KC_P9,  KC_P0,  KC_PMNS, KC_PEQL     , KC_TSTOG,
  	TT(_RAISE),KC_LEFT,KC_DOWN,KC_RIGHT,KC_PGDN,KC_PSLS,KC_TAB,KC_P4, KC_P5,  KC_P6,  KC_PDOT,KC_PAST,KC_PENT    , XXXXXXX,
  	_______,   XXXXXXX,KC_DEL, KC_INS, KC_NO,  KC_PAST,KC_P0,  KC_P1,  KC_P2,  KC_P3,  KC_PSLS ,_______,   XXXXXXX,XXXXXXX,
    _______  ,_______  ,_______,KC_BSPC              ,XXXXXXX          ,_______,_______  ,_______ ,XXXXXXX,XXXXXXX,XXXXXXX
    )
};

#ifdef ENCODER_ENABLE       // Encoder Functionality
bool encoder_update_keymap(uint8_t index, bool clockwise) {
    switch (index) {
        case 0:         // Top left encoder
            encoder_action_volume(clockwise);
            break;
        default:
            break;
    }
    return true;  // fall to encoder_update_user and encoder_update_kb definitions
}
#endif
