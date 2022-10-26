/*
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

#define _FUNC   MO(_FN)
#define _LSADEL LSA_T(KC_DEL)
#define _AGRHOM RALT_T(KC_HOME)
#define _CTLEND RCTL_T(KC_END)
#define _CTLALT LCTL(KC_LALT)
#define _LSNUBS LSFT_T(KC_NUBS)
#define _MINMIZ LGUI(KC_D)

// Layer shorthand
enum layer_names {
    _ZERO,
    _FN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
    [_ZERO] = LAYOUT_ansi(
       KC_ESC,    KC_BSLS,KC_GRV,  KC_1,     KC_2,   KC_3,   KC_4,   KC_5,                       KC_6,   KC_7,   KC_8,   KC_9,     KC_0,   KC_MINS,KC_EQL,KC_BSPC,
       KC_INS,         KC_TAB,   KC_Q,       KC_W,   KC_E,   KC_R,   KC_T,                       KC_Y,   KC_U,   KC_I,   KC_O,       KC_P,   KC_LBRC,KC_RBRC,KC_BSPC,
                 KC_LCTL,      KC_A,         KC_S,   KC_D,   KC_F,   KC_G,                       KC_H,   KC_J,   KC_K,   KC_L,         KC_SCLN,KC_QUOT,  KC_ENT,
           KC_LSFT,          KC_Z,           KC_X,   KC_C,   KC_V,   KC_B,   _LSADEL,    KC_LGUI,KC_N,   KC_M,   KC_COMM,KC_DOT,         KC_SLSH,KC_RSFT,      KC_UP,
                 _FUNC,                                  KC_LALT,    KC_SPC,             _AGRHOM,                                          _CTLEND,    KC_LEFT,KC_DOWN,KC_RGHT
    ), 

    
    [_FN] = LAYOUT_ansi(
       _MINMIZ,   _______,_______,   KC_F1,    KC_F2,  KC_F3,  KC_F4,  KC_F5,                    KC_F6,  KC_F7,  KC_F8,  KC_F9,    KC_F10, KC_F11, KC_F12, _______,
       KC_CALC,      _______,    _______,    _______,_______,QK_BOOT,  _______,                    _______,_______,KC_INS ,_______,    KC_PSCR,_______,_______,_______,
                 KC_CAPS,      _______,      KC_SLCK,_______,_______,_______,                    _______,_______,_______,_______,      _______,_______,_______,
           _LSNUBS,          _______,        _______,_______,_______,KC_PAUS,_______,    KC_RGUI,_______,KC_MENU,_______,_______,        _______,_______,      KC_PGUP,
                 _______,                                _CTLALT,    KC_DEL,             _______,                                          _______,    _______,KC_PGDN,_______
    )
};
