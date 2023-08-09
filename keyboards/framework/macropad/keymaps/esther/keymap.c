// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     *         ┌───────┬───────┬───────┬───────┐
     *  4 keys │ RGB + │ RGB - │RGB Nxt│RGB Prv│
     *         │Brightn│Brightn│Effect │Effect │
     *         ├───────┼───────┼───────┼───────┤
     *  4 keys │Numpad │       │       │ CTRL+A│
     *         │Layer  │       │       │       │
     *         ├───────┼───────┼───────┼───────┤
     *  4 keys │ Enter │       │       │ Delete│
     *         │       │       │       │       │
     *         ├───────┼───────┼───────┼───────┤
     *  4 keys │ Save  │  A    │  V    │ Cut   │
     *         │       │       │       │       │
     *         ├───────┼───────┼───────┼───────┤
     *  4 keys │   +   │ CTRL  │ Undo  │ Copy  │
     *         │       │  +    │       │       │
     *         ├───────┼───────┼───────┼───────┤
     *  4 keys │   -   │ CTRL  │ Redo  │ Paste │
     *         │       │  -    │       │       │
     *         └───────┴───────┴───────┴───────┴
     * 24 total
     */
    [0] = LAYOUT(
        RGB_VAI, RGB_VAD,   RGB_MOD, RGB_RMOD,
        TG(1),   XXXXXXX,   XXXXXXX, C(KC_A),
        KC_ENT,  XXXXXXX,   XXXXXXX, KC_DEL,
        C(KC_S), KC_A,      KC_V,    C(KC_X),
        KC_PPLS, C(KC_EQL), C(KC_Z), C(KC_C),
        KC_PMNS, C(KC_MINS),C(KC_Y), C(KC_V)
    ),
     /* Numpad
     *         ┌────┬────┬────┬────┐
     *  4 keys │Esc │Calc│ =  │ <- │
     *         ├────┼────┼────┼────┤
     *  4 keys │ Num│ /  │ *  │ -  │
     *         ├────┼────┼────┼────┤
     *  3 keys │ 7  │ 8  │ 9  │ +  │
     *         ├────┼────┼────┼────┤
     *  4 keys │ 4  │ 5  │ 6  │ +  │
     *         ├────┼────┼────┼────┤
     *  3 keys │ 1  │ 2  │ 3  │Entr│
     *         ├────┼────┼────┼────┤
     *  3 keys │ 0  │ 0  │ .  │Entr│
     *         └────┼────┴────┴────┴
     * 21 total
     */
    [1] = LAYOUT(
        KC_ESC,  KC_CALC, KC_EQL,  KC_BSPC,
        _______, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_P0,   KC_PDOT, KC_PENT
    )
};
// clang-format on
