/*
MIT License
Copyright (c) 2023 Sebastian Stumpf

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_6(
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,                                                       S(KC_A),    S(KC_B),    S(KC_C),    S(KC_D),    S(KC_E),
        KC_F,    KC_G,    KC_H,    KC_I,    KC_J,      KC_K,                                   S(KC_F), S(KC_G),    S(KC_H),    S(KC_I),    S(KC_J),    S(KC_K),
        KC_L,    KC_M,    KC_N,    KC_O,    KC_P,      KC_Q, KC_R, KC_S,     S(KC_L), S(KC_M), S(KC_N), S(KC_O),    S(KC_P),    S(KC_Q),    S(KC_R),    S(KC_S),
                                                       KC_T, KC_U, KC_V,     S(KC_T), S(KC_U), S(KC_V)
    )
};
