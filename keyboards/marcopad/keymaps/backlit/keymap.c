// Copyright (c) 2022 Marco Pelegrini <marco@pelegrini.ca>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ 7 │ 8 │ 9 │
     * ├───┼───┼───┤
     * │ 4 │ 5 │ 6 │
     * ├───┼───┼───┤
     * │ 1 │ 2 │ 3 │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_3x3(
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3
    )
};

const uint16_t PROGMEM backlight_next[] = {KC_P7, KC_P8, COMBO_END};
const uint16_t PROGMEM backlight_toggle[] = {KC_P8, KC_P9, COMBO_END};
combo_t key_combos[] = {
    COMBO(backlight_next, UG_NEXT),
    COMBO(backlight_toggle, UG_TOGG)
};
