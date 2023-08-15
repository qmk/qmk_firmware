// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     *         ┌───────┬───────┬───────┬───────┐
     *  4 keys │ RGB   │RGB Nxt│ RGB + │ Sleep │
     *         │Toggle │Effect │Brightn│       │
     *         ├───────┼───────┼───────┼───────┤
     *  4 keys │Numpad │RGB Prv│ RGB - │ RGB BL│
     *         │Layer  │Effect │Brightn│ Step  │
     *         ├───────┼───────┼───────┼───────┤
     *  4 keys │ RGB + │ RGB + │ RGB + │  <--  │
     *         │ Hue   │ Sat   │ Speed │       │
     *         ├───────┼───────┼───────┼───────┤
     *  4 keys │ RGB - │ RGB - │ RGB - │ Enter │
     *         │ Hue   │ Sat   │ Speed │       │
     *         ├───────┼───────┼───────┼───────┤
     *  4 keys │       │  Up   │       │       │
     *         │       │       │       │       │
     *         ├───────┼───────┼───────┼───────┤
     *  4 keys │ Left  │ Down  │ Right │       │
     *         │       │       │       │       │
     *         └───────┴───────┴───────┴───────┘
     * 24 total
     */
    [0] = LAYOUT(
        RGB_TOG, RGB_MOD, RGB_VAI, KC_SLEP,
        TG(1),   RGB_RMOD,RGB_VAD, BL_STEP,
        RGB_HUI, RGB_SAI, RGB_SPI, KC_BSPC,
        RGB_HUD, RGB_SAD, RGB_SPD, KC_ENT,
        XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX,
        KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX
    ),
     /* Numpad
     *         ┌────┬────┬────┬────┐
     *  4 keys │Esc │Calc│ =  │ <- │
     *         ├────┼────┼────┼────┤
     *  4 keys │    │ /  │ *  │ -  │
     *         ├────┼────┼────┼────┤
     *  4 keys │ 7  │ 8  │ 9  │ +  │
     *         ├────┼────┼────┼────┤
     *  4 keys │ 4  │ 5  │ 6  │ +  │
     *         ├────┼────┼────┼────┤
     *  4 keys │ 1  │ 2  │ 3  │Entr│
     *         ├────┼────┼────┼────┤
     *  4 keys │ 0  │ 0  │ .  │Entr│
     *         └────┴────┴────┴────┘
     * 24 total
     */
    [1] = LAYOUT(
        KC_ESC,  KC_CALC, KC_EQL,  KC_BSPC,
        _______, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_P0,   KC_PDOT, KC_PENT
    ),
     /* Alphabet
     *         ┌────┬────┬────┬────┐
     *  4 keys │ A  │ B  │ C  │ D  │
     *         ├────┼────┼────┼────┤
     *  4 keys │ E  │ F  │ G  │ H  │
     *         ├────┼────┼────┼────┤
     *  4 keys │ I  │ J  │ K  │ L  │
     *         ├────┼────┼────┼────┤
     *  4 keys │ M  │ N  │ O  │ P  │
     *         ├────┼────┼────┼────┤
     *  4 keys │ Q  │ R  │ S  │ T  │
     *         ├────┼────┼────┼────┤
     *  4 keys │ U  │ V  │ W  │ X  │
     *         └────┴────┴────┴────┘
     * 24 total
     */
    [2] = LAYOUT(
        KC_A,    KC_B,    KC_C,    KC_D,
        KC_E,    KC_F,    KC_G,    KC_H,
        KC_I,    KC_J,    KC_K,    KC_L,
        KC_M,    KC_N,    KC_O,    KC_P,
        KC_Q,    KC_R,    KC_S,    KC_T,
        KC_U,    KC_V,    KC_W,    KC_X
    )
};
// clang-format on
