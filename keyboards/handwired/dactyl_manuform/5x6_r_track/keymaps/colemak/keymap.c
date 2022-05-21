/* Copyright
 *  2020 Qurn
 *  2022 Pascal Jaeger
 *  ______     _____
 * |_   __ \  |_   _|
 *   | |__) |   | |
 *   |  ___/ _  | |
 *  _| |_   | |_| |
 * |_____|  \.___.'
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "../../trackball_functions.h"

#define _COLEMAK 0

#define _LOWER 1
#define _RAISE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_5x6(
DM_REC1,    DM_REC1, DM_PLY1, DM_REC2 , DM_PLY2 , DM_RSTP,               KC_CPI_DOWN, KC_CPI_STD , KC_CPI_UP , KC_SMO_SC , KC_0        ,KC_QUOT_MY,
KC_TAB,     KC_Q ,   KC_W   , KC_F    , KC_P    , KC_B   ,               KC_J    ,    KC_L       , KC_U      , KC_Y      , KC_SCLN_INV ,KC_QUOT_MY,
KC_ESC,     KC_A ,   KC_R   , KC_S    , KC_T    , KC_G   ,               KC_M    ,    KC_N       , KC_E      , KC_I      , KC_O        ,KC_MINS,
KC_TILD_MY, KC_Z ,   KC_X   , KC_C    , KC_D    , KC_V   ,               KC_K    ,    KC_H       , KC_COMM   , KC_DOT    , KC_SLSH     ,KC_BSLASH,
                           _______, _______,                                         _______, KC_LGUI,
                                       TD(SFT_TM),    TD(RAI_TM),          _______, KC_SPC,
                                       TD(CTL_TM),    TD(GUI_TM),          _______, KC_ENT,
                                       TD(ALT_TM),    TD(LOW_TM),          KC_BSPC, KC_DEL
),

[_LOWER] = LAYOUT_5x6(

KC_TILD, KC_EXLM     , KC_AT   , KC_HASH   , KC_DLR  ,KC_PERC,           KC_CIRC, KC_AMPR , KC_ASTR    , KC_LPRN  , KC_RPRN   ,           _______,
_______, KC_PGDN     , KC_HOME , KC_END    , KC_PGUP ,_______,           _______, _______ , RALT(KC_Y) , _______  , RALT(LSFT(KC_SCLN)) , _______,
_______, RALT(KC_Q)  , _______ ,RALT(KC_S) , KC_RBRC ,_______,           KC_BTN3, KC_BTN1 , RALT(KC_5) , KC_BTN2  , RALT(KC_P),           _______,
KC_F12 , KC_F1       , KC_F2   , KC_F3     , KC_F4   , KC_F5 ,           KC_F6  , KC_F7   , KC_F8      , KC_F9    , KC_F10    ,           KC_F11 ,
                            _______,_______,                             _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______
),

[_RAISE] = LAYOUT_5x6(
_______, _______ , _______ , _______ , _______ ,_______,                 _______, _______      , _______      , _______     , _______     , _______,
_______,  KC_1   , KC_2    , KC_3    , KC_4    , KC_5  ,                 KC_6   , KC_7         , KC_8         , KC_9        , KC_0        , KC_QUOT,
_______, KC_LPRN , KC_RPRN , KC_LBRC , KC_RBRC ,KC_LBRC,                 KC_RBRC, LSFT(KC_LBRC),LSFT(KC_RBRC) ,LSFT(KC_COMM),LSFT(KC_DOT) ,KC_MS_BTN3,
KC_TILD, KC_EXLM , KC_AT   , KC_HASH , KC_DLR  ,KC_PERC,                 KC_CIRC, KC_AMPR      , KC_ASTR      , KC_PLUS     , KC_EQL      , KC_DEL,
                             _______,_______,                                _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______

),
};
