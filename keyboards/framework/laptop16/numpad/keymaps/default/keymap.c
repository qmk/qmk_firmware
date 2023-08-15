// Copyright 2022-2023 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     *         ┌────┬────┬────┬────┐
     *  4 keys │Esc │Calc│ =  │ <- │
     *         ├────┼────┼────┼────┤
     *  4 keys │ Num│ /  │ *  │ -  │
     *         ├────┼────┼────┼────┤
     *  3 keys │ 7  │ 8  │ 9  │    │
     *         ├────┼────┼────┤    │
     *  4 keys │ 4  │ 5  │ 6  │ +  │
     *         ├────┼────┼────┼────┤
     *  3 keys │ 1  │ 2  │ 3  │    │
     *         ├────┴────┼────┤    │
     *  3 keys │ 0       │ .  │Entr│
     *         └─────────┴────┴────┴
     * 21 total
     */
    [_NUMLOCK] = LAYOUT(
        KC_ESC,  KC_CALC, KC_EQL,  KC_BSPC,
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
            KC_P0,        KC_PDOT, KC_PENT
    ),
     /*
     * Extra keys for when numlock is disabled.
     * Numlock keys are passed through to the number layer,
     * and automatically remapped by the OS.
     *         ┌────┬────┬────┬────┐
     *  4 keys │    │    │    │    │
     *         ├────┼────┼────┼────┤
     *  4 keys │    │    │    │    │
     *         ├────┼────┼────┼────┤
     *  3 keys │Home│ ↑  │PgUp│BL  │
     *         ├────┼────┼────┤Brtg│
     *  4 keys │ ←  │    │ →  │    |
     *         ├────┼────┼────┼────┤
     *  3 keys │End │ ↓  │PdDn│BL  │
     *         ├────┴────┼────┤Step│
     *  3 keys │ Insert  │Del │    │
     *         └─────────┴────┴────┴
     * 21 total
     */
    [_FN] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, BL_BRTG,
        _______, _______, _______,
            _______,      _______, BL_STEP

    )

};
// clang-format on

bool led_update_user(led_t led_state) {
    // Change layer if numlock state changes, either triggered by OS or
    // by numlock key on this keyboard
    if (led_state.num_lock) {
        layer_off(_FN);
    } else {
        layer_on(_FN);
    }
    return true;
}
