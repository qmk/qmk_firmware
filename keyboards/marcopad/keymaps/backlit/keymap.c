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
    COMBO(backlight_next, RGB_MODE_FORWARD),
    COMBO(backlight_toggle, RGB_TOG),
    COMBO(hue_up, RGB_HUI),
    COMBO(hue_down, RGB_HUD),
    COMBO(sat_up, RGB_SAI),
    COMBO(sat_down, RGB_SAD),
    COMBO(value_up, RGB_VAI),
    COMBO(value_down, RGB_VAD),
    COMBO(speed_up, RGB_SPI),
    COMBO(speed_down, RGB_SPD)
};
