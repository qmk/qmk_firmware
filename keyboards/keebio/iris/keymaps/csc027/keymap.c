/*
Copyright 2020 Constantine Chen @csc027

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
#include "csc027.h"

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT_wrapper(
        _____________________QWERTY_L1_____________________,                            _____________________QWERTY_R1_____________________,
        _____________________QWERTY_L2_____________________,                            _____________________QWERTY_R2_____________________,
        _____________________QWERTY_L3_____________________,                            _____________________QWERTY_R3_____________________,
        _____________________QWERTY_L4_____________________, KC_SPC,           KC_SPC,  _____________________QWERTY_R4_____________________,
                                   KC_LGUI,  KC_LALT,  KC_SPC,                    KC_SPC,   KC_RALT,  KC_RGUI
    ),

    [_RS] = LAYOUT_wrapper(
        ______________________RAISE_L1_____________________,                            ______________________RAISE_R1_____________________,
        ______________________RAISE_L2_____________________,                            ______________________RAISE_R2_____________________,
        ______________________RAISE_L3_____________________,                            ______________________RAISE_R3_____________________,
        ______________________RAISE_L4_____________________, _______,          _______, ______________________RAISE_R4_____________________,
                                   _______,  _______,  _______,                   _______,  _______,  _______
    ),

    [_LW] = LAYOUT_wrapper(
        ______________________LOWER_L1_____________________,                            ______________________LOWER_R1_____________________,
        ______________________LOWER_L2_____________________,                            ______________________LOWER_R2_____________________,
        ______________________LOWER_L3_____________________,                            ______________________LOWER_R3_____________________,
        ______________________LOWER_L4_____________________, _______,          _______, ______________________LOWER_R4_____________________,
                                   _______,  _______,  _______,                   _______,  _______,  _______
    ),

    [_MS] = LAYOUT_wrapper(
        ______________________MOUSE_L1_____________________,                            ______________________MOUSE_R1_____________________,
        ______________________MOUSE_L2_____________________,                            ______________________MOUSE_R2_____________________,
        ______________________MOUSE_L3_____________________,                            ______________________MOUSE_R3_____________________,
        ______________________MOUSE_L4_____________________, _______,          _______, ______________________MOUSE_R4_____________________,
                                   _______,  _______,  _______,                   _______,  _______,  _______
    ),

    [_WT] = LAYOUT_wrapper(
        ________________WINDOWS_TERMINAL_L1________________,                            ________________WINDOWS_TERMINAL_R1________________,
        ________________WINDOWS_TERMINAL_L2________________,                            ________________WINDOWS_TERMINAL_R2________________,
        ________________WINDOWS_TERMINAL_L3________________,                            ________________WINDOWS_TERMINAL_R3________________,
        ________________WINDOWS_TERMINAL_L4________________, _______,          _______, ________________WINDOWS_TERMINAL_R4________________,
                                   _______,  _______,  _______,                   _______,  _______,  _______
    ),

    [_CN] = LAYOUT_wrapper(
        ___________________CONVENIENCE_L1__________________,                            ___________________CONVENIENCE_R1__________________,
        ___________________CONVENIENCE_L2__________________,                            ___________________CONVENIENCE_R2__________________,
        ___________________CONVENIENCE_L3__________________,                            ___________________CONVENIENCE_R3__________________,
        ___________________CONVENIENCE_L4__________________, _______,          _______, ___________________CONVENIENCE_R4__________________,
                                   _______,  _______,  _______,                   _______,  _______,  _______
    ),

    [_GG] = LAYOUT(
        KC_5,    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_T,    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_G,    MC_LSEC, KC_A,    KC_S,    KC_D,    KC_F,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_B,    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_SPC,  KC_SPC,          _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  TO(_CS), TO(_QW),
                                   KC_LALT,  KC_V,     KC_SPC,                    _______,  KC_M,     KC_B
    ),

    [_CS] = LAYOUT(
        XXXXXXX, KC_5,    KC_1,    KC_2,    KC_3,    KC_4,                               KC_6,    KC_P7,   KC_P8,   KC_P9,   KC_0,    KC_BSPC,
        XXXXXXX, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,                               KC_Y,    KC_P4,   KC_P5,   KC_P6,   XXXXXXX, KC_NLCK,
        KC_G,    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,                               KC_H,    KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_ESC,
        XXXXXXX, KC_LCTL, XXXXXXX, KC_X,    XXXXXXX, XXXXXXX, KC_SPC,           _______, KC_N,    KC_P0,   KC_P0,   KC_PDOT, TO(_QW), TO(_QW),
                                   KC_B,     KC_SPC,   KC_SPC,                    _______,  KC_N,     KC_P0
    )
};
