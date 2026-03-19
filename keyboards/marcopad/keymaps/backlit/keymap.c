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
const uint16_t PROGMEM backlight_toggle[] = {KC_P7, KC_P9, COMBO_END};
const uint16_t PROGMEM hue_up[] = {KC_P7, KC_P4, COMBO_END};
const uint16_t PROGMEM hue_down[] = {KC_P7, KC_P1, COMBO_END};
const uint16_t PROGMEM sat_up[] = {KC_P7, KC_P5, COMBO_END};
const uint16_t PROGMEM sat_down[] = {KC_P7, KC_P2, COMBO_END};
const uint16_t PROGMEM value_up[] = {KC_P7, KC_P6, COMBO_END};
const uint16_t PROGMEM value_down[] = {KC_P7, KC_P3, COMBO_END};
const uint16_t PROGMEM speed_up[] = {KC_P8, KC_P4, COMBO_END};
const uint16_t PROGMEM speed_down[] = {KC_P8, KC_P1, COMBO_END};
combo_t key_combos[] = {
    COMBO(backlight_next, RM_NEXT),
    COMBO(backlight_toggle, RM_TOGG),
    COMBO(hue_up, RM_HUEU),
    COMBO(hue_down, RM_HUED),
    COMBO(sat_up, RM_SATU),
    COMBO(sat_down, RM_SATD),
    COMBO(value_up, RM_VALU),
    COMBO(value_down, RM_VALD),
    COMBO(speed_up, RM_SPDU),
    COMBO(speed_down, RM_SPDD)
};
