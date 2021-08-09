/* Copyright 2021 Yaroslav Smirnov <elorenn@bk.ru>
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

enum layers { _QWERTY, _LOWER, _RAISE, _ADJUST };

#define LOWER TT(_LOWER)
#define RAISE MO(_RAISE)

#define M_SHLL   LCTL(KC_LSFT)
#define M_SHLA   LCTL(KC_LALT)
#define M_BBSLS  LSFT(KC_BSLS)
#define M_FLEFT  LCTL(KC_LEFT)
#define M_FRIGHT LCTL(KC_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_5(
        KC_ESC  ,  KC_Q   ,  KC_W   ,  KC_E   ,  KC_R   ,  KC_T  ,                   KC_Y   ,  KC_U   ,  KC_I   ,  KC_O   , KC_P    , KC_BSPC ,
        KC_LBRC ,  KC_A   ,  KC_S   ,  KC_D   ,  KC_F   ,  KC_G  ,                   KC_H   ,  KC_J   ,  KC_K   ,  KC_L   , KC_SCLN , KC_QUOT ,
        KC_RBRC ,  KC_Z   ,  KC_X   ,  KC_C   ,  KC_V   ,  KC_B  ,                   KC_N   ,  KC_M   , KC_COMM , KC_DOT  , KC_SLSH , KC_GRAVE,
                  KC_LGUI , KC_LCTL , KC_LSFT , LOWER   , M_SHLL ,                  M_SHLA  ,  RAISE  , KC_SPC  , KC_LALT , KC_ENT
    ),

    [_LOWER] = LAYOUT_split_3x6_5(
        KC_ESC  , KC_PDOT , KC_PMNS , KC_PPLS , KC_MINS , KC_EQL ,                  KC_MUTE , KC_MSTP , KC_MPLY , KC_MPRV , KC_MNXT , KC_BSPC ,
        KC_PAST ,  KC_1   ,  KC_2   ,  KC_3   ,  KC_4   ,  KC_5  ,                   KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  , KC_F5   , KC_F6   ,
        KC_PSLS ,  KC_6   ,  KC_7   ,  KC_8   ,  KC_9   ,  KC_0  ,                   KC_F7  ,  KC_F8  ,  KC_F9  , KC_F10  , KC_F11  , KC_F12  ,
                  KC_LGUI , KC_LCTL , KC_LSFT , KC_TRNS , M_SHLL ,                  M_SHLA  , KC_TRNS , KC_SPC  , KC_LALT , KC_ENT
    ),
    
    [_RAISE] = LAYOUT_split_3x6_5(
        KC_ESC  ,     KC_PDOT   ,   M_BBSLS , KC_BSLS   , LSFT(KC_MINS), LSFT(KC_EQL),                  KC_HOME , KC_WH_L ,  KC_UP  , KC_WH_R , KC_PGUP , KC_BSPC ,
        KC_TAB  ,     LSFT(KC_1), LSFT(KC_2), LSFT(KC_3),  LSFT(KC_4)  , LSFT(KC_5)  ,                  M_FLEFT , KC_LEFT , KC_DOWN , KC_RIGHT, M_FRIGHT, KC_DEL  ,
        LSFT(KC_TAB), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8),  LSFT(KC_9)  , LSFT(KC_0)  ,                   KC_END , KC_F22 ,  KC_F23  , KC_CAPS , KC_PGDN , MO(_ADJUST),
                        KC_LGUI , KC_LCTL   , KC_LSFT   ,  KC_LALT    , M_SHLL       ,                  M_SHLA  , KC_TRNS , KC_SPC  , KC_RALT , KC_ENT
    ),

     [_ADJUST] = LAYOUT_split_3x6_5(
        KC_NO   , KC_SLEP , KC_VOLU , KC_BRIU , KC_NO   , KC_NO  ,                  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NLCK ,
        KC_NO   , KC_WAKE , KC_VOLD , KC_BRID , KC_NO   , KC_NO  ,                  KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,
        KC_NO   , KC_NO   , KC_NO   , KC_F13  , KC_F14  , KC_F15 ,                  KC_F16  , KC_F17  , KC_F18  , KC_NO   , KC_NO   , MO(_ADJUST),
                  RESET   , KC_NO   , KC_NO   , KC_TRNS , KC_NO  ,                  KC_NO   , KC_TRNS , KC_TRNS , KC_NO   , KC_NO
    )
};
