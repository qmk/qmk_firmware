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

#define CUT LCTL(KC_X)
#define COPY LCTL(KC_C)
#define PSTE LCTL(KC_V)
#define UNDO LCTL(KC_Z)
#define SLCTA LCTL(KC_A)
#define APPFW LALT(KC_TAB)
#define MG_A LGUI_T(KC_A)
#define MA_S LALT_T(KC_S)
#define MC_D LCTL_T(KC_D)
#define MS_F LSFT_T(KC_F)
#define MS_J LSFT_T(KC_J)
#define MC_K LCTL_T(KC_K)
#define MA_L LALT_T(KC_L)
#define MG_SCLN LGUI_T(KC_SCLN)
#define TASKM RCS(KC_ESC)
#define L1_SPC LT(1, KC_SPC)
#define L2_BS LT(2, KC_BSPC)
#define DTMGR LGUI(KC_TAB)
#define REDO LCTL(KC_Y)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_6(
        KC_Q, KC_W, KC_E, KC_R, KC_T,                                                         KC_Y, KC_U,   KC_I,    KC_O,    KC_P,
        MG_A, MA_S, MC_D, MS_F, KC_G, KC_MUTE,                                         TASKM, KC_H, MS_J,   MC_K,    MA_L, MG_SCLN,
        KC_Z, KC_X, KC_C, KC_V, KC_B,     CUT,   COPY,   PSTE,          SLCTA, APPFW,   UNDO, KC_N, KC_M, KC_DOT, KC_COMM, KC_SLSH,
                                       KC_ESC, L1_SPC, KC_TAB,         KC_ENT, L2_BS, KC_DEL
    ),
    [1] = LAYOUT_split_3x5_6(
        KC_F1,     KC_F2, KC_F3,   KC_F4,  KC_F5,                                                                KC_F6,   KC_F7,   KC_F8,   KC_F9, KC_F10,
        KC_1,       KC_2,  KC_3,    KC_4,   KC_5, KC_TRNS,                                            KC_TRNS,    KC_6,    KC_7,    KC_8,    KC_9,   KC_0,
        KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_GRV, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,   DTMGR,    REDO, KC_BSLS, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,
                                                    KC_NO, KC_TRNS,   KC_NO,        KC_LALT, KC_RSFT, KC_RCTL
    ),
    [2] = LAYOUT_split_3x5_6(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F11,                                                                KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                     KC_TRNS, QK_BOOT, KC_TRNS,          KC_NO, KC_TRNS, KC_NO
    )
};
