/*
Copyright 2023 Dan White <opensource@bluetufa.com>

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
#include "badger.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY]     = LAYOUT(
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        MOVE_MAC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL,  KC_RALT, KC_LGUI, LT_SPACE,         KC_SPC,            J_FUNCT, KC_RALT, J_MACRO
    ),
    [_MOVE]       = LAYOUT(
        MAC_WND,  IJ_STEP, IJ_INTO, IJ_OUT,  IJ_RUN,  IJ_STOP,  IJ_TOP,  WD_BACK, KC_HOME, KC_END,  WD_FRWD, WD_DELE,
        _______,  MM_LH,   MM_MAX,  MM_RH,   IJ_FIND, IJ_LINE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, KC_QUOT,
        _______,  MM_LEFT, MM_RGHT, MAC_CPY, MAC_SPS, _______,  IJ_BOTT, IJ_REN,  IJ_BACK, IJ_FWD,  KC_UP,   _______,
        _______,  _______, _______, _______,          _______,           _______, _______, _______
    ),
    [_MACRO]      = LAYOUT(
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        _______,  MAC_ALL, MAC_SAV, MAC_DUP, MAC_FND, _______,  KC_BSLS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
        _______,  MAC_UND, MAC_CUT, MAC_CPY, MAC_PST, MAC_B,    _______, _______, _______, _______, KC_SCLN, _______,
        _______,  _______, _______, _______,          _______,           _______, _______, _______
    ),
    [_FUNCTION]   = LAYOUT(
        KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
        _______,  MAC_ALL, MAC_SAV, MAC_DUP, KC_MINS, KC_COLN,  KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_LCBR, KC_DQUO,
        _______,  MAC_UND, MAC_CUT, MAC_CPY, MAC_PST, MAC_B,    _______, _______, _______, KC_COLN, KC_DQUO, _______,
        _______,  _______, _______, _______,          _______,           _______, _______, CONFIG
    ),
    [_CONFIG]     = LAYOUT(
        QK_BOOT,  _______, _______, _______, IJ_RFMT, _______,  _______, _______, _______, _______, _______, _______,
        KC_CAPS,  RGB_TOG, BL_DOWN, DB_TOGG, RGB_M_P, RGB_M_B,  RGB_M_SN,RGB_M_R, RGB_M_SW,KC_F11,  KC_F12,  _______,
        _______,  RGB_HUI, RGB_HUD, RGB_M_K, RGB_M_X, RGB_M_G,  RGB_M_T, RGB_VAI, RGB_VAD, _______, _______, _______,
        _______,  _______, _______, _______,          _______,           _______, _______, _______
    )
};
